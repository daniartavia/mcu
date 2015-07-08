#Desinstalar MCU
sudo -v
echo "Eliminando MCU"
echo "Eliminando el binario de /usr/bin"
sudo rm /usr/bin/mcu
echo "Quitando permisos a MCU"
sudo sh -c "sed -i \"/ ALL=(ALL) NOPASSWD:\/usr\/bin\/mcu/d\" /etc/sudoers"
echo "MCU ha sido desinstalado correctamente"
