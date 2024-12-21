CREATE DATABASE Seminar62;

USE Seminar62

CREATE TABLE Tipuri(
	id INT PRIMARY KEY IDENTITY,
	descriere VARCHAR(100)
);

CREATE TABLE Oras(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(100),
);

CREATE TABLE Restaurant(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(100),
	adresa VARCHAR(100),
	telefon VARCHAR(100),
	idOras INT FOREIGN KEY REFERENCES Oras(id),
	idTip INT FOREIGN KEY REFERENCES Tipuri(id)
);

CREATE TABLE Utilizatori(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(100),
	email VARCHAR(100),
	parola VARCHAR(100),
);

 CREATE TABLE Note(
	idRestaurant INT FOREIGN KEY REFERENCES Restaurant(id),
	idUtilizator INT FOREIGN KEY REFERENCES Utilizatori(id),
	nota FLOAT,
	CONSTRAINT PK_Nota PRIMARY KEY (idRestaurant, idUtilizator)
 );

 INSERT INTO Tipuri(descriere) VALUES
 ('Pub'),('Fine dining'),('Club'),('Exclusive')

 INSERT INTO Oras(nume) VALUES
 ('Cluj'),('Oradea'),('Bucuresti')

 INSERT INTO Restaurant(nume,adresa,telefon,idOras,idTip) VALUES
 ('Rod','Strada1','1',1,2), ('Sumeshi','Strada2','2',1,1), ('DolceVita','Strada3','3',1,3), ('Pomet','Strada4','4',1,4), 
 ('NOBU','Strada5','5',2,2), ('Rummu','Strada6','6',2,4), ('Taverna','Strada7','7',3,4)

 INSERT INTO Utilizatori(nume,email,parola) VALUES
 ('Andrei','a@yahoo.com','aa'), ('Mihai','m@yahoo.com','mm'), ('Cosmin','c@yahoo.com','cc'), ('Ion','i@yahoo.com','ii')

 INSERT INTO Note(idUtilizator,idRestaurant,nota) VALUES
 (1,1,10),(1,2,9),(1,3,6),(2,4,10),(2,5,8),(3,6,9),(4,7,4)



 --Creați o procedură stocată care primește un restaurant, un utilizator și o notă și adaugă nota dată 
 --de către utilizator restaurantului. Dacă utilizatorul a dat deja o notă acelui restaurant, 
 --valoarea notei va fi actualizată. 
 GO 
 CREATE OR ALTER PROCEDURE UpsertNota @idR INT, @idU INT, @nota FLOAT AS
 BEGIN
	IF EXISTS(SELECT * FROM Note WHERE idRestaurant=@idR AND idUtilizator=@idU)
	BEGIN
		UPDATE Note
		SET nota=@nota WHERE idRestaurant=@idR AND idUtilizator=@idU
		PRINT 'Nota exista, o actualizam'
	END
	ELSE
	BEGIN
		INSERT INTO Note(idRestaurant,idUtilizator,nota) VALUES (@idR,@idU,@nota)
		PRINT 'Nota nu exista, o adaugam'
	END

 END
 GO

 EXEC UpsertNota 1,1,10
 EXEC UpsertNota 7,1,8

 SELECT * FROM Note

--Creati o funcție care primește ca parametru de intrare adresa de email a unui utilizator 
--și afișează numele tipului de restaurant, numele și numărul de telefon al restaurantului, orașul, nota, 
--numele și adresa de email a utilizatorului pentru toate evaluările utilizatorului care are adresa de email 
--egală cu cea transmisă prin intermediul parametrului de intrare

GO 
CREATE OR ALTER FUNCTION Functie (@email VARCHAR(100))
RETURNS TABLE AS
RETURN SELECT T.descriere as TipRestaurant, R.nume as NumeRestaurant, R.telefon as TelefonRestaurant, 
O.nume as NumeOras, N.nota as Nota, U.nume as NumeUtilizator, U.email as EmailUtilizator FROM Utilizatori U
INNER JOIN Note N ON N.idUtilizator=U.id
INNER JOIN Restaurant R ON R.id=N.idRestaurant
INNER JOIN Tipuri T ON T.id=R.idTip
INNER JOIN Oras O ON O.id=R.idOras
WHERE U.email=@email
GO

SELECT * FROM dbo.Functie('a@yahoo.com')

