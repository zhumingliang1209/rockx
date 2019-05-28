
set -e

sudo rm -rf /etc/udev/rules.d/91-rk1808-ai-cs.rules

sudo rm -rf /usr/local/bin/npu_transfer_proxy
#sudo rm -rf /etc/systemd/system/npu_transfer_proxy.service

echo "uninstall ok"