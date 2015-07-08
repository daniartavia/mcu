#Instalador de MCU
sudo -v
echo "Instalación de MCU"
echo "Compilando MCU"
g++ mcu.cpp -o mcu `pkg-config --cflags --libs gtk+-3.0`
echo "Moviendo binario de MCU a /usr/bin"
sudo mv mcu /usr/bin/mcu
echo "Dando permisos a MCU"
sudo sh -c "echo $USER' ALL=(ALL) NOPASSWD:/usr/bin/mcu' >> /etc/sudoers"
echo "MCU ha sido instalado correctamente. Ejecute 'mcu -h' para más infomación"
