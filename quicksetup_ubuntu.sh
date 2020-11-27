sudo apt update
sudo apt install -y build-essential vim git cscope libncurses-dev libssl-dev bison flex emacs git-mail
sudo apt install -y  wget linux-tools-common linux-tools-generic linux-tools-`uname -r`

cd ~
#wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.9.11.tar.xz
#tar xf linux-5.9.11.tar.xz

git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
