if ! command -v brew &> /dev/null
then
  export HOME_BREW="/goinfre/$USER"
  rm -rf $HOME/.brew && rm -rf $HOME_BREW/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME_BREW/.brew && export PATH=$HOME_BREW/.brew/bin:$PATH && brew update
	echo	"export PATH=$HOME_BREW/.brew/bin:$PATH" >> ~/.zshrc
    brew install readline
fi