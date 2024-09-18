#include <iostream>
#include <string>

using namespace std;

const int MAX_MOVIES = 10;
const int MAX_ROOMS = 5;
const int MAX_SEATS = 10;
const int MAX_SCHEDULES = 20;

class Movie {
public:
	string title;
	int year;
	int duration;
	string country;
	string review;
};

class Room {
public:
	int number;
	int seatCount;
	double price;
};

class Schedule {
public:
	string date;
	string startTime;
	string endTime;
	int movieIndex;
	int roomIndex;
};

class Customer {
public:
	string id;
	string creditCard;
};

Movie movies[MAX_MOVIES];
Room rooms[MAX_ROOMS];
Schedule schedules[MAX_SCHEDULES];
Customer customer;

int movieCount = 0;
int roomCount = 0;
int scheduleCount = 0;

bool seats[MAX_ROOMS][MAX_SEATS];

void showMenu() {
	cout << "\n--- Sistema de Venta de Tiquetes ---\n";
	cout << "1. Acerca de\n";
	cout << "2. Mantenimiento de Peliculas\n";
	cout << "3. Mantenimiento de Salas\n";
	cout << "4. Mantenimiento de Horarios\n";
	cout << "5. Reservar Asiento\n";
	cout << "6. Vender Tiquete\n";
	cout << "7. Salir\n";
}

void showAbout() {
	cout << "\nSistema de Venta de Tiquetes para Cine 2.0\n";
	cout << "Desarrollado por Victor Quesada Prado para NUEVA CINEMA SA, Perez Zeledon\n";
}

void exitSystem() {
	cout << "\nGracias por usar el sistema. Hasta pronto!\n";
}

void addMovie() {
	if(movieCount < MAX_MOVIES) {
		cout << "\n--- Agregar Pelicula ---\n";
		cout << "Ingrese el nombre de la pelicula: ";
		cin.ignore();
		getline(cin, movies[movieCount].title);
		
		cout << "Ingrese el ano de la pelicula: ";
		cin >> movies[movieCount].year;
		
		cout << "Ingrese la duracion de la pelicula (en minutos): ";
		cin >> movies[movieCount].duration;
		
		cout << "Ingrese el pais de origen: ";
		cin.ignore();
		getline(cin, movies[movieCount].country);
		
		cout << "Ingrese una breve resena: ";
		getline(cin, movies[movieCount].review);
		
		movieCount++;
		cout << "Pelicula agregada exitosamente!\n";
	} else {
		cout << "No se pueden agregar mas peliculas, se ha alcanzado el limite.\n";
	}
}

void displayMovies() {
	if(movieCount > 0) {
		cout << "\n--- Lista de Peliculas ---\n";
		for(int i = 0; i < movieCount; i++) {
			cout << "Pelicula " << (i + 1) << ":\n";
			cout << "Nombre: " << movies[i].title << endl;
			cout << "Ano: " << movies[i].year << endl;
			cout << "Duracion: " << movies[i].duration << " minutos\n";
			cout << "Pais: " << movies[i].country << endl;
			cout << "Resena: " << movies[i].review << endl;
			cout << "--------------------------\n";
		}
	} else {
		cout << "No hay peliculas registradas.\n";
	}
}

void manageMovies() {
	int option;
	do {
		cout << "\n--- Mantenimiento de Peliculas ---\n";
		cout << "1. Agregar Pelicula\n";
		cout << "2. Mostrar Peliculas\n";
		cout << "3. Regresar al Menu Principal\n";
		cout << "Seleccione una opcion: ";
		cin >> option;
		
		switch(option) {
		case 1: addMovie(); break;
		case 2: displayMovies(); break;
		case 3: return;
		default: cout << "Opcion no valida. Intente de nuevo." << endl;
		}
	} while(option != 3);
}

void addRoom() {
	if(roomCount < MAX_ROOMS) {
		cout << "\n--- Agregar Sala ---\n";
		cout << "Ingrese el numero de la sala: ";
		cin >> rooms[roomCount].number;
		
		cout << "Ingrese la cantidad de butacas: ";
		cin >> rooms[roomCount].seatCount;
		
		cout << "Ingrese el precio por butaca: ";
		cin >> rooms[roomCount].price;
		
		roomCount++;
		cout << "Sala agregada exitosamente!\n";
	} else {
		cout << "No se pueden agregar mas salas, se ha alcanzado el limite.\n";
	}
}

void displayRooms() {
	if(roomCount > 0) {
		cout << "\n--- Lista de Salas ---\n";
		for(int i = 0; i < roomCount; i++) {
			cout << "Sala " << (i + 1) << ":\n";
			cout << "Numero de Sala: " << rooms[i].number << endl;
			cout << "Cantidad de Butacas: " << rooms[i].seatCount << endl;
			cout << "Precio por Butaca: " << rooms[i].price << endl;
			cout << "--------------------------\n";
		}
	} else {
		cout << "No hay salas registradas.\n";
	}
}

void manageRooms() {
	int option;
	do {
		cout << "\n--- Mantenimiento de Salas ---\n";
		cout << "1. Agregar Sala\n";
		cout << "2. Mostrar Salas\n";
		cout << "3. Regresar al Menu Principal\n";
		cout << "Seleccione una opcion: ";
		cin >> option;
		
		switch(option) {
		case 1: addRoom(); break;
		case 2: displayRooms(); break;
		case 3: return;
		default: cout << "Opcion no valida. Intente de nuevo." << endl;
		}
	} while(option != 3);
}

void initializeSeats() {
	for (int i = 0; i < MAX_ROOMS; i++) {
		for (int j = 0; j < MAX_SEATS; j++) {
			seats[i][j] = false;
		}
	}
}

void displaySeats(int room) {
	cout << "\nButacas de la sala " << (room + 1) << ":\n";
	for (int i = 0; i < rooms[room].seatCount; i++) {
		cout << "Butaca " << (i + 1) << ": " << (seats[room][i] ? "Reservada" : "Disponible") << endl;
	}
}

bool reserveSpecificSeat(int room, int seat) {
	if (!seats[room][seat]) {
		seats[room][seat] = true;
		return true;
	} else {
		return false;
	}
}

void reserveSeat() {
	if (movieCount == 0 || roomCount == 0 || scheduleCount == 0) {
		cout << "Debe haber al menos una pelicula, una sala y un horario registrados antes de realizar una reserva.\n";
		return;
	}
	
	int selectedMovie, selectedRoom, selectedSchedule;
	
	displayMovies();
	cout << "Seleccione una pelicula (1-" << movieCount << "): ";
	cin >> selectedMovie;
	selectedMovie--;
	
	displayRooms();
	cout << "Seleccione una sala (1-" << roomCount << "): ";
	cin >> selectedRoom;
	selectedRoom--;
	
	displaySeats(selectedRoom);
	
	int seatNumber;
	cout << "Seleccione un numero de butaca (1-" << rooms[selectedRoom].seatCount << "): ";
	cin >> seatNumber;
	seatNumber--;
	
	if (reserveSpecificSeat(selectedRoom, seatNumber)) {
		cout << "Butaca reservada exitosamente!\n";
	} else {
		cout << "Butaca ya esta reservada. Intente con otra.\n";
	}
}

void addSchedule() {
	if (scheduleCount < MAX_SCHEDULES && movieCount > 0 && roomCount > 0) {
		cout << "\n--- Agregar Horario ---\n";
		cout << "Ingrese la fecha (dd-mm-aaaa): ";
		cin >> schedules[scheduleCount].date;
		
		cout << "Ingrese la hora de inicio (hh:mm): ";
		cin >> schedules[scheduleCount].startTime;
		
		cout << "Ingrese la hora de finalizacion (hh:mm): ";
		cin >> schedules[scheduleCount].endTime;
		
		displayMovies();
		cout << "Seleccione la pelicula (1-" << movieCount << "): ";
		cin >> schedules[scheduleCount].movieIndex;
		schedules[scheduleCount].movieIndex--;
		
		displayRooms();
		cout << "Seleccione la sala (1-" << roomCount << "): ";
		cin >> schedules[scheduleCount].roomIndex;
		schedules[scheduleCount].roomIndex--;
		
		scheduleCount++;
		cout << "Horario agregado exitosamente!\n";
	} else {
		cout << "No se pueden agregar mas horarios o no hay peliculas/salas disponibles.\n";
	}
}

void displaySchedules() {
	if (scheduleCount > 0) {
		cout << "\n--- Lista de Horarios ---\n";
		for (int i = 0; i < scheduleCount; i++) {
			cout << "Horario " << (i + 1) << ":\n";
			cout << "Fecha: " << schedules[i].date << endl;
			cout << "Inicio: " << schedules[i].startTime << endl;
			cout << "Finalizacion: " << schedules[i].endTime << endl;
			cout << "Pelicula: " << movies[schedules[i].movieIndex].title << endl;
			cout << "Sala: " << rooms[schedules[i].roomIndex].number << endl;
			cout << "--------------------------\n";
		}
	} else {
		cout << "No hay horarios registrados.\n";
	}
}

void manageSchedules() {
	int option;
	do {
		cout << "\n--- Mantenimiento de Horarios ---\n";
		cout << "1. Agregar Horario\n";
		cout << "2. Mostrar Horarios\n";
		cout << "3. Regresar al Menu Principal\n";
		cout << "Seleccione una opcion: ";
		cin >> option;
		
		switch(option) {
		case 1: addSchedule(); break;
		case 2: displaySchedules(); break;
		case 3: return;
		default: cout << "Opcion no valida. Intente de nuevo." << endl;
		}
	} while(option != 3);
}

void sellTicket() {
	if (movieCount == 0 || roomCount == 0 || scheduleCount == 0) {
		cout << "Debe haber al menos una pelicula, una sala y un horario registrados antes de vender un tiquete.\n";
		return;
	}
	
	int selectedMovie, selectedRoom, selectedSchedule;
	
	displayMovies();
	cout << "Seleccione una pelicula (1-" << movieCount << "): ";
	cin >> selectedMovie;
	selectedMovie--;
	
	displayRooms();
	cout << "Seleccione una sala (1-" << roomCount << "): ";
	cin >> selectedRoom;
	selectedRoom--;
	
	displaySeats(selectedRoom);
	
	int seatNumber;
	cout << "Seleccione un numero de butaca (1-" << rooms[selectedRoom].seatCount << "): ";
	cin >> seatNumber;
	seatNumber--;
	
	if (seats[selectedRoom][seatNumber]) {
		cout << "Tiquete vendido exitosamente!\n";
	} else {
		cout << "La butaca seleccionada no esta reservada. No se puede vender el tiquete.\n";
	}
}

int main() {
	initializeSeats();
	
	int option;
	
	do {
		showMenu();
		cout << "Seleccione una opcion: ";
		cin >> option;
		
		switch(option) {
		case 1: showAbout(); break;
		case 2: manageMovies(); break;
		case 3: manageRooms(); break;
		case 4: manageSchedules(); break;
		case 5: reserveSeat(); break;
		case 6: sellTicket(); break;
		case 7: exitSystem(); break;
		default: cout << "Opcion no valida. Intente de nuevo.\n";
		}
	} while(option != 7);
	
	return 0;
}
