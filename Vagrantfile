IP = "192.168.66.120"
NAME = "x6502.dev"

Vagrant.configure("2") do |config|

    config.vm.box = "precise64"
    config.vm.box_url = "http://files.vagrantup.com/precise64.box"
    config.vm.network "private_network", ip: IP

    config.vm.provider :virtualbox do |virtualbox|
        virtualbox.customize ["modifyvm", :id, "--name", NAME]
        virtualbox.customize ["modifyvm", :id, "--natdnshostresolver1", "on"]
        virtualbox.customize ["modifyvm", :id, "--memory", "512"]
        virtualbox.customize ["setextradata", :id, "--VBoxInternal2/SharedFoldersEnableSymlinksCreate/v-root", "1"]
    end

    config.ssh.username = "vagrant"
    config.ssh.shell = "bash -l"
    config.ssh.keep_alive = true
    config.ssh.forward_agent = false
    config.ssh.forward_x11 = false
    config.vagrant.host = :detect

    config.vm.provision :shell, :inline => "sudo apt-get install -y make clang xa65"

end
