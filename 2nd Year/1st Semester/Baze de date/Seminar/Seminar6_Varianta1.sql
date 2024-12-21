CREATE DATABASE Seminar6;

USE Seminar6;

-- DE CITIT SEMINAR 4

CREATE TABLE Tipuri(
	id INT PRIMARY KEY IDENTITY(1,1),
	descriere VARCHAR(100),
);

CREATE TABLE Trenuri(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(100),
	tip INT FOREIGN KEY REFERENCES Tipuri(id)
);

CREATE TABLE Rute(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(100),
	tren INT FOREIGN KEY REFERENCES Trenuri(id)
);

CREATE TABLE Statii(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(100)
);

CREATE TABLE RuteStatii(
	idRuta INT FOREIGN KEY REFERENCES Rute(id),
	idStatie INT FOREIGN KEY REFERENCES Statii(id),
	oraSosirii TIME,
	oraPlecarii TIME,
	CONSTRAINT PK_Rute_Statii PRIMARY KEY(idRuta, idStatie)

);

INSERT INTO Tipuri(descriere) VALUES
('regional'),('inter-regional'),('privat');

INSERT INTO Trenuri(nume,tip) VALUES
('tren A',1),('tren AaA',1),('tren B',2),('tren C',3),('tren D',3)

INSERT INTO Rute(nume,tren) VALUES
('Cluj-Orade',1),('Cluj-Arad',2),('Cluj-Costinesti',3),('Constanta-Cluj',3),('Carei-Bod',4)

INSERT INTO Statii(nume) VALUES
('Brasov'),('Teius'),('Ploiesti'),('Dej')

INSERT INTO RuteStatii(idRuta,idStatie,oraPlecarii,oraSosirii) VALUES
(1,4,'11:11:00','11:13:00'),(2,2,'14:31:00','14:32:00'),(3,1,'09:00:00','09:00:50'),
(4,3,'20:34:00','20:40:00'),(5,1,'23:01:00','23:50:00')

INSERT INTO RuteStatii(idRuta,idStatie,oraPlecarii,oraSosirii) VALUES
(1,2,'11:11:00','11:13:00'),(2,1,'14:31:00','14:32:00'),(3,3,'09:00:00','09:00:50'),
(4,4,'20:34:00','20:40:00'),(5,4,'23:01:00','23:50:00')

INSERT INTO RuteStatii(idRuta,idStatie,oraPlecarii,oraSosirii) VALUES
(1,3,'11:11:00','11:13:00'),(1,1,'14:31:00','14:32:00')

SELECT * FROM Trenuri
SELECT * FROM Tipuri
SELECT * FROM Rute
SELECT * FROM Statii
SELECT * FROM RuteStatii


GO
CREATE OR ALTER PROCEDURE UpsertRutaStatie @idRuta INT, @idStatie INT, @oraS TIME, @oraP TIME AS
BEGIN
	IF EXISTS(SELECT * FROM RuteStatii WHERE idRuta=@idRuta AND idStatie=@idStatie)
	BEGIN
		UPDATE RuteStatii SET oraPlecarii=@oraP, oraSosirii=@oraS WHERE idRuta=@idRuta AND idStatie=@idStatie
		PRINT 'RutaStatie exista, actualizam datele'
	END
	ELSE
	BEGIN
		INSERT INTO RuteStatii(idRuta,idStatie,oraPlecarii,oraSosirii) VALUES (@idRuta,@idStatie,@oraP,@oraS)
		PRINT 'RutaStaie nu exista, o inseram in tabel'
	END
END
GO

EXEC UpsertRutaStatie 2,1,'23:23:23','23:25:00'
EXEC UpsertRutaStatie 2,3,'23:23:23','23:25:00'



-- View care afiseaza numele rutelor care contin toate statiile
GO
CREATE OR ALTER VIEW View_Rute 
AS
	SELECT DISTINCT R.id, R.nume FROM Rute R
	INNER JOIN RuteStatii RS ON RS.idRuta=R.id
	INNER JOIN Statii S on S.id=RS.idStatie
	GROUP BY R.id, R.nume
	HAVING COUNT(*) = (SELECT COUNT(*) FROM Statii)
GO

SELECT * FROM View_Rute

