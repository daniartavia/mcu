#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void apaga_openrc () {
	system("sudo halt");
}

static void reinicia_openrc () {
	system("sudo reboot");
}

static void apaga_systemd () {
	system("sudo systemctl poweroff");
}

static void reinicia_systemd () {
	system("sudo systemctl reboot");
}

static void apaga_generico () {
	system("sudo shutdown -h now");
}

static void reinicia_generico () {
	system("sudo shutdown -r now");
}

static void cierra_sesion () {
	system("openbox --exit"); //Openbox
	system("echo 'awesome.quit()' | awesome-client"); //Awesome
	system("gnome-session-quit"); //Gnome?
	system("DISPLAY=:0 qdbus org.kde.ksmserver /KSMServer logout 0 0 0"); //KDE 5 ?
	system("i3exit logout"); //I3 ?
	system("xfce4-session-logout --logout"); //XFCE4 ?
}

static void bloquea () {
	system("xscreensaver-command --lock");
}

static void detecta () {
	FILE *output = popen("sudo rc -V", "r");
	if (!output) {
		printf("Error");
	}
	char buffer[1024];
	char *line_p = fgets(buffer, sizeof(buffer), output);
	if (strstr(line_p,"OpenRC") != NULL) {
		printf("Init detectado: openrc\n");
		exit(0);
	}
	pclose(output);

	FILE *output2 = popen("sudo systemctl --version", "r");
	if (!output2) {
		printf("Error");
	}
	char buffer2[1024];
	char *line_p2 = fgets(buffer2, sizeof(buffer2), output2);
	if (strstr(line_p2,"systemd") != NULL) {
		printf("Init detectado: systemd\n");
		exit(0);
	} else {
		printf("Init no reconocido\n");
		exit(0);
	}
	pclose(output2);
}

static void ayuda() {
	printf("\nMCU - Menú de Cierre Universal \n\n");
	printf("Este menú esta supuesto para funcionar en la mayoría de inits y entornos de escritorio o gestores de ventanas.\n");
	printf("Soporte conocido para los siguientes demonios de inicio:\n\n OpenRC \n Systemd\n\n");
	printf("\nSoporte conocido para los siguientes entornos y gestores de ventanas:\n\n");
	printf(" OpenBox\n Awesome\n Gnome\n KDE 5\n I3 \n\n");
	printf("Opciones:\n\n");
	printf(" -ao | Apagar OpenRC\n");
	printf(" -as | Apagar Systemd\n");
	printf(" -ag | Apagado generico (supuesto para funcionar en cualquier init)\n");
	printf(" -ro | Reinciar OpenRC\n");
	printf(" -rs | Reinciar Systemd\n");
	printf(" -rg | Reinicio generico (supuesto para funcionar en cualquier init)\n");
	printf(" -cs | Cerrar sesión\n");
	printf(" -b  | Bloquear la pantalla con xscreensaver\n");
	printf(" -d  | Detecta y muestra el demonio de inicio\n");
	printf(" -h  | Muestra este menú de ayuda\n\n\n");
	printf("Este programa ha sido escrito por Dani Artavia bajo los terminos de la licencia GPL\n");
	printf("Gracias por usar MCU ;-)\n\n");
}

int main (int argc, char* argv[]) {
	for(int i = 1; i < argc; i++) {
		if(i + 1 == argc) {
			if(strcmp(argv[i],"-ao") == 0) {
				apaga_openrc();
			} else if (strcmp(argv[i],"-as") == 0) {
				apaga_systemd();
			} else if (strcmp(argv[i],"-ag") == 0) {
				apaga_generico();
			} else if (strcmp(argv[i],"-ro") == 0) {
				reinicia_openrc();
			} else if (strcmp(argv[i],"-rs") == 0) {
				reinicia_systemd();
			} else if (strcmp(argv[i],"-rg") == 0) {
				reinicia_generico();
			} else if (strcmp(argv[i],"-cs") == 0) {
				cierra_sesion();
			} else if (strcmp(argv[i],"-b") == 0) {
				bloquea();
			} else if (strcmp(argv[i],"-h") == 0) {
				ayuda();
			} else if (strcmp(argv[i],"-d") == 0) {
				detecta();
			} else {
				printf("Por favor, ingrese una opción valida\n");
			}
		}
	}
}
