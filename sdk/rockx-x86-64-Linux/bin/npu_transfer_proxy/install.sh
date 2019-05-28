
set -e

PWD=$( cd "$( dirname $0 )" && cd -P "$( dirname "$SOURCE" )" && pwd )

cat <<EOF > "91-rk1808-ai-cs.rules"
SUBSYSTEM=="usb", ATTR{idVendor}=="2207", MODE="0666"
EOF
sudo cp -f 91-rk1808-ai-cs.rules /etc/udev/rules.d/
rm 91-rk1808-ai-cs.rules
sudo udevadm control --reload-rules
sudo udevadm trigger
sudo ldconfig

sudo cp ${PWD}/npu_transfer_proxy /usr/local/bin/npu_transfer_proxy
#sudo cp ${PWD}/npu_transfer_proxy.service /etc/systemd/system/npu_transfer_proxy.service

echo "install ok"