CREATE DATABASE LLAB2;

USE LLAB2;

CREATE TABLE Eveniment (
    id_eveniment INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    data_eveniment DATE NOT NULL,
    descriere VARCHAR(200),
);


CREATE TABLE Locatie (
    id_locatie INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    adresa VARCHAR(100) NOT NULL UNIQUE,
    capacitate INT
);
CREATE TABLE Eveniment_Locatie (
    id_eveniment INT,
    id_locatie INT,
    PRIMARY KEY (id_eveniment, id_locatie),
    CONSTRAINT FK_EvenimentL FOREIGN KEY (id_eveniment)
    REFERENCES Eveniment(id_eveniment),
    CONSTRAINT FK_Locatie FOREIGN KEY (id_locatie)
    REFERENCES Locatie(id_locatie)
);

CREATE TABLE Barman (
    id_barman INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    prenume VARCHAR(100) NOT NULL,
    ani_experienta INT,
);

CREATE TABLE Ospatar (
    id_ospatar INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    prenume VARCHAR(100) NOT NULL,
    ani_experienta INT,
);

CREATE TABLE Casier (
    id_casier INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    prenume VARCHAR(100) NOT NULL,
);

CREATE TABLE Garderobier (
    id_garderobier INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    prenume VARCHAR(100) NOT NULL,
    nr_haine_in_garderoba INT,
);

CREATE TABLE DJ (
    id_dj INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    prenume VARCHAR(100) NOT NULL,
    gen_muzica VARCHAR(100) UNIQUE,
    experienta INT NOT NULL,
);

CREATE TABLE Paza (
    id_paza INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    prenume VARCHAR(100) NOT NULL,
    nume_firma VARCHAR(100),
);
CREATE TABLE Eveniment_Barman(
    id_eveniment INT,
    id_barman INT,
    PRIMARY KEY (id_eveniment, id_barman),
    CONSTRAINT FK_Eveniment_Barman_Eveniment FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT FK_Eveniment_Barman_Barman FOREIGN KEY (id_barman) REFERENCES Barman(id_barman) ON UPDATE CASCADE ON DELETE CASCADE
);	
CREATE TABLE Eveniment_Casier (
    id_eveniment INT,
    id_casier INT,
    PRIMARY KEY (id_eveniment, id_casier),
    CONSTRAINT FK_Eveniment_Casier_Eveniment FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT FK_Eveniment_Casier_Casier FOREIGN KEY (id_casier) REFERENCES Casier(id_casier) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Eveniment_Garderobier (
    id_eveniment INT,
    id_garderobier INT,
    PRIMARY KEY (id_eveniment, id_garderobier),
    CONSTRAINT FK_Eveniment_Garderobier_Eveniment FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT FK_Eveniment_Garderobier_Garderobier FOREIGN KEY (id_garderobier) REFERENCES Garderobier(id_garderobier) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Eveniment_DJ (
    id_eveniment INT,
    id_dj INT,
    PRIMARY KEY (id_eveniment, id_dj),
    CONSTRAINT FK_Eveniment_DJ_Eveniment FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT FK_Eveniment_DJ_DJ FOREIGN KEY (id_dj) REFERENCES DJ(id_dj) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Eveniment_Paza (
    id_eveniment INT,
    id_paza INT,
    PRIMARY KEY (id_eveniment, id_paza),
    CONSTRAINT FK_Eveniment_Paza_Eveniment FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT FK_Eveniment_Paza_Paza FOREIGN KEY (id_paza) REFERENCES Paza(id_paza) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Eveniment_Ospatar (
    id_eveniment INT,
    id_ospatar INT,
    PRIMARY KEY (id_eveniment, id_ospatar),
    CONSTRAINT FK_Eveniment_Ospatar_Eveniment FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT FK_Eveniment_Ospatar_Ospatar FOREIGN KEY (id_ospatar) REFERENCES Ospatar(id_ospatar) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Mese (
    id_masa INT PRIMARY KEY IDENTITY(1,1),
    id_eveniment INT NOT NULL,
    locuri INT,
    CONSTRAINT FK_Eveniment_Mese FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment) ON UPDATE CASCADE ON DELETE CASCADE,
	CONSTRAINT ck_Mese CHECK (locuri>=1 and locuri<=10) 
);

CREATE TABLE Clienti (
    id_client INT PRIMARY KEY IDENTITY(1,1),
    id_masa INT,
    nume VARCHAR(100) NOT NULL,	
    prenume VARCHAR(100) NOT NULL,
    CONSTRAINT FK_Masa_Clienti FOREIGN KEY (id_masa) REFERENCES Mese(id_masa) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Eveniment_Clienti (
    id_eveniment INT,
    id_client INT,
    PRIMARY KEY (id_eveniment, id_client),
    CONSTRAINT FK_EvenimentC FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment),
    CONSTRAINT FK_Client FOREIGN KEY (id_client) REFERENCES Clienti(id_client)
);


