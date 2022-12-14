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
