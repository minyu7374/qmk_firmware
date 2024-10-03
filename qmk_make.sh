#!/bin/bash
# set -x

# make <my_keyboard>:<my_keymap>
# make <my_keyboard>:<my_keymap>:flash

# qmk compile -kb <my_keyboard> -km <my_keymap>
# qmk flash -kb <my_keyboard> -km <my_keymap>

cd "$(dirname "$0")" || exit 1

keyboard_def=jqqr/minyu
keymap_def=hhkb_ext

help-info() {
    echo -e "Usage:\n\t$0 [OPTION]..."
    echo '
    OPTION:
        -k, --keyboard  <PARM>        default '"$keyboard_def"'
        -m, --keymap    <PARM>        default '"$keymap_def"'
        -f, --flash                   flash
        -v, --via                     enable via feature
        -b, --bootmagic               open bootmagic feature
        -c, --combo                   open combo feature
        -u, --custom-macro            open user custom macro
        -p, --passwd                  input password for CK_PWD macro
        -A, --ALL                     enable all function (-A == -vbcu)
        -h, --help                    show help info
    '
}

read_passwd() {
    echo -n "Enter Password for $1: "
    # read -s -r pwd; echo
    # [ -n "$pwd" ] && {
        # #  local def="-D$1=\"${pwd//\"/\\\"}\""; #echo "$def"
        # # local def_trans; def_trans="$(echo -n "$def" | sed 's/\\/\\\\/g; s/"/\\"/g; s/#/\\#/g')"; #echo "$def_trans"
        # # passwd_macros+=("$def_trans")
    # }
    # 通过extra_flags方式传入密码宏定义对特殊字符的兼容性太差，改为修改config.h的方式
    read -s -r "$1"; echo
}

post_parms() {
    # minyu keyboard 没有物理reset键，必须至少开启bootmagic
    [ "$keyboard" == "minyu" ] && bootmagic=true

    keymaps_dir="keyboards/$keyboard/keymaps"
}

parse_parms() {
    temp=$(getopt -o k:m:fvbcupAh --long keyboard:,keymap:,flash,via,bootmagic,combo,custom-macro,passwd,all,help -n "$0" -- "$@") || {
        echo "Terminating..." >&2
        exit 1
    }
    eval set -- "$temp"

    keyboard=$keyboard_def
    keymap=$keymap_def
    flash=false
    via=false
    bootmagic=false
    combo=false
    macro=false
    # passwd_macros=()
    passwds=(USER_PASSWD ROOT_PASSWD)
    tmp_code_prefix="/tmp/qmk_minyu_$(uuidgen)_"

    while true; do
        case "$1" in
        -h| --help)
            help-info
            exit 0
            ;;
        -k | --keyboard)
            if [ -n "$2" ]; then keyboard=$2; fi
            shift 2
            ;;
        -m | --keymap)
            if [ -n "$2" ]; then keymap=$2; fi
            shift 2
            ;;
        -f | --flash)
            flash=true
            shift
            ;;
        -v | --via)
            via=true
            shift
            ;;
        -b | --bootmagic)
            bootmagic=true
            shift
            ;;
        -c | --combo)
            combo=true
            shift
            ;;
        -u | --custom)
            macro=true
            shift
            ;;
		-A | --ALL)
			for fun in via bootmagic combo macro; do eval "$fun"=true; done
			shift
			;;
        -p | --passwd)
            for pwd in "${passwds[@]}"; do read_passwd "$pwd"; done
            shift
            ;;
        --)
            shift
            break
            ;;
        *)
            echo "Internal error!" >&2
            exit 1
            ;;
        esac
    done
}

passwd_define() {
    for pwd in "${passwds[@]}"; do
        local val; val="$(eval "echo \${$pwd}")"
        [ -n "$val" ] && echo "#define $pwd \"${val//\"/\\\"}\"" \
            >> "$(readlink -f "$keymaps_dir/$keymap/config.h")"

    done
}

open_feature() {
    for fea in "$@"; do
        sed -i --follow-symlinks "s/$fea.*/$fea = yes/" "$keymaps_dir/$keymap/rules.mk"
    done
}

diff_conf() {
    for f in config.h rules.mk; do
        echo -e "\ndiff $f with _default:"
        diff "$keymaps_dir"/{_default,"$keymap"}/"$f"
    done; echo
}

pre_make() {
    [ -d "$keymaps_dir/$keymap" ] || exit 2
    for f in config.h rules.mk; do
        cp {"$keymaps_dir/_default/","$tmp_code_prefix"}"$f"
        ln -sf "$tmp_code_prefix$f" "$keymaps_dir/$keymap/$f"
    done
}

post_make() {
    cd "$keymaps_dir/$keymap" && \
    for f in config.h rules.mk; do
        ln -sf {../_default/,}"$f"
        rm "$tmp_code_prefix$f"
    done
}

do_make() {
    local target="$keyboard:$keymap"
    [ "$flash" == true ] && target+=":flash"

    # [ "$macro" == true ] && { extra_flags+=" -DCUSTOM_MACRO_OPEN ${passwd_macros[*]}" }
    [ "$macro" == true ] && { extra_flags+=" -DCUSTOM_MACRO_OPEN"; passwd_define; }
    [ "$combo" == true ] && { extra_flags+=" -DCOMBO_OPEN"; open_feature COMBO_ENABLE; }
    [ "$via" == true ] && open_feature VIA_ENABLE VIA_QMK_SUPPORT_ENABLE
    [ "$bootmagic" == true ] && open_feature BOOTMAGIC_ENABLE

    diff_conf
    make clean
    make EXTRAFLAGS="$extra_flags" "$target"
}

parse_parms "$@"
post_parms

pre_make
trap post_make EXIT
do_make
