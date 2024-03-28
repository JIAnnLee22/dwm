#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ra='ranger'
alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '

EDITOR=nvim
alias nvi='nvim'
alias vi='vim'

export HISTTIMEFORMAT='%F %T '
export HISTCONTROL=ignoreboth
# export PATH=
export ANDROID_SDK_ROOT=~/Android/Sdk
export GRADLE_LOCAL_JAVA_HOME=/usr/lib/jvm/java-11-openjdk

export PUB_HOSTED_URL="https://pub.flutter-io.cn"
export FLUTTER_STORAGE_BASE_URL="https://storage.flutter-io.cn"
