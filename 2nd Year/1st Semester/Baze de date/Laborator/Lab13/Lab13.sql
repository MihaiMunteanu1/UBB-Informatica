CREATE DATABASE Lab13;

USE Lab13;

CREATE TABLE Producatori(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50),
	siteWeb VARCHAR(50)
);

CREATE TABLE TipuriDesert(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50)
);

CREATE TABLE Deserturi(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50),
	modPreparare VARCHAR(50),
	pret FLOAT,
	nrCalorii INT,
	idP INT FOREIGN KEY REFERENCES Producatori(id),
	idTD INT FOREIGN KEY REFERENCES TipuriDesert(id)
);

CREATE TABLE Clienti(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50),
	email VARCHAR(50),
	data DATE
);

CREATE TABLE Achizitii(
	idC INT FOREIGN KEY REFERENCES Clienti(id),
	idD INT FOREIGN KEY REFERENCES Deserturi(id),
	cantitate INT,
	CONSTRAINT PK_Achizitii PRIMARY KEY(idC,idD)
);

INSERT INTO Producatori(nume,siteWeb) VALUES
('Pralina','a'),('Deliciu','b'),('VladMuresan','c'),('Saveur','d')

INSERT INTO TipuriDesert(nume) VALUES
('tort'),('acadea'),('inghetata'),('clatita')

INSERT INTO Deserturi(nume,modPreparare,pret,nrCalorii,idP,idTD) VALUES
('Cheescake','coacere',10,140,1,1),('LavaCake','coacere',20,340,1,1),
('BananaSplit','inghetare',25,600,2,3),('Ecler','coacere',14,300,2,1),('Pancakes','coacere',20,300,2,4),
('ChupaChups','inghetare',25,100,4,2),('TrioChocolate','coacere',40,1000,4,1)

INSERT INTO Clienti(nume,email,data) VALUES
('Andrei','a','10/10/2004'),('Eric','e','10/10/2003'),('Vlad','v','10/10/2002')

INSERT INTO Achizitii(idC,idD,cantitate) VALUES
(1,2,2),(1,4,4),
(2,7,3),(2,3,4),(2,5,7),
(3,6,4),(3,3,3)


GO
CREATE OR ALTER PROCEDURE UpsertAchizitie @idC INT, @idD INT, @cantitate INT AS
BEGIN
	IF EXISTS (SELECT * FROM Achizitii WHERE idC=@idC AND idD=@idD)
	BEGIN
		UPDATE Achizitii SET cantitate=@cantitate WHERE idC=@idC AND idD=@idD
		PRINT 'Achizitia exista, actualizam cantitatea'
	END
	ELSE
	BEGIN
		INSERT INTO Achizitii(idC,idD,cantitate) VALUES (@idC,@idD,@cantitate)
		PRINT 'Achizitia nu exista, o adaugam'
	END
END
GO

SELECT * FROM Achizitii

exec UpsertAchizitie 1,3,100

