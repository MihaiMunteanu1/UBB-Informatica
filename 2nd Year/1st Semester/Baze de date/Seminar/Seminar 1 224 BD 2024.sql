--crearea unei baze de date 
CREATE DATABASE ProblemaFilme224;
GO
--conectarea la baza de date creata mai sus
USE ProblemaFilme224;
CREATE TABLE Utilizatori
(cod_u INT PRIMARY KEY IDENTITY,
nume_u VARCHAR(100) NOT NULL UNIQUE,
parola VARCHAR(100),
email VARCHAR(100) 
);
CREATE TABLE Companii
(cod_c INT PRIMARY KEY IDENTITY(1,1),
nume_c NVARCHAR(100),
tara NVARCHAR(100)
);
CREATE TABLE Filme
(cod_f INT PRIMARY KEY IDENTITY,
titlu NVARCHAR(200),
durata TIME,
limba NVARCHAR(100),
cod_c INT FOREIGN KEY REFERENCES Companii(cod_c) ON UPDATE CASCADE 	ON DELETE CASCADE
);
CREATE TABLE Note
(cod_u INT,
cod_f INT,
nota INT,
CONSTRAINT fk_UtilizatoriNote FOREIGN KEY (cod_u) REFERENCES 	Utilizatori(cod_u),
CONSTRAINT fk_FilmeNote FOREIGN KEY (cod_f) REFERENCES Filme(cod_f),
CONSTRAINT pk_Note PRIMARY KEY (cod_u, cod_f)
);
--crearea unei constrangeri UNIQUE
ALTER TABLE Utilizatori
ADD CONSTRAINT uq_email UNIQUE (email);
--crearea unei constrangeri CHECK
ALTER TABLE Note
ADD CONSTRAINT ck_nota CHECK (nota>=1 AND nota<=10);
--modificarea numelui bazei de date
ALTER DATABASE ProblemaFilme224
MODIFY Name=NoteFilme224BD;
--stergerea unei baze de date
--USE master;
--DROP DATABASE NoteFilme224BD;


