CREATE DATABASE Practic;

USE Practic;


CREATE TABLE Tari(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50) NOT NULL,
	nr_loc INT NOT NULL
);

CREATE TABLE Companii(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50) NOT NULL,
	datai DATE NOT NULL,
	rating INT CHECK(rating >=1 and rating <=5) NOT NULL,
	idTara INT FOREIGN KEY REFERENCES Tari(id)
);


CREATE TABLE Certificari(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50) NOT NULL,
	descriere VARCHAR(50) NOT NULL,
	data_lansarii date NOT NULL,
	versiune INT NOT NULL,
	nivel INT NOT NULL,
	idC INT FOREIGN KEY REFERENCES Companii(id)
);

CREATE TABLE Angajati(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50) NOT NULL,
	prenume VARCHAR(50) NOT NULL,
	datan DATE NOT NULL,
	email VARCHAR(50) NOT NULL,
	telefon VARCHAR(50) NOT NULL
);

CREATE TABLE CertificariAngajati(
	idA INT FOREIGN KEY REFERENCES Angajati(id),
	idC INT FOREIGN KEY REFERENCES Certificari(id),
	data_examinarii DATE NOT NULL,
	pretul FLOAT NOT NULL,
	punctaj INT NOT NULL
	CONSTRAINT PK_CA PRIMARY KEY(idA,idC)
)

INSERT INTO Tari(nume,nr_loc) VALUES
('Romania',20000000),('Spania',40000000),('Germania',60000000)

SELECT * FROM Tari

INSERT INTO Companii(nume,datai,rating,idTara) VALUES
('NTT Data','10/10/2004',5,3),('Tora','02/02/2008',4,1),('SEAT-Soft','11/11/2010',2,2)

SELECT * FROM Companii

INSERT INTO Certificari(nume,descriere,data_lansarii,versiune,nivel,idC) VALUES
('Certificare1','buna','12/12/2012',6,5,1),('Certificare2','rea','12/12/2018',9,2,2),
('Certificare3','foarte buna','03/04/2020',10,7,3),('Certificare4','excelenta','01/01/2023',15,8,1)

SELECT * FROM Certificari

INSERT INTO Angajati(nume,prenume,datan,email,telefon) VALUES
('Andrei','Marian','06/06/2004','a@yahoo.com','0767612121'),
('Mihai','Rusu','08/11/2003','m@yahoo.com','071268321'),
('Alex','Muresan','09/10/2004','am@yahoo.com','0735612121'),
('Ovidiu','Anca','10/12/2002','ov@yahoo.com','0713456121')

SELECT * FROM Angajati

INSERT INTO CertificariAngajati(idA,idC,data_examinarii,pretul,punctaj) VALUES
(1,1,'08/09/2014',1000,98),(1,2,'08/09/2019',1000,99),(1,3,'08/09/2021',1000,88),
(2,1,'06/01/2016',3000,60),(2,3,'06/01/2021',3000,80),
(3,2,'05/02/2019',4000,50),(3,4,'05/02/2024',4000,90),
(4,4,'04/03/2024',2500,74),(4,3,'04/03/2023',2500,94)

SELECT * FROM CertificariAngajati

GO
CREATE OR ALTER PROCEDURE Upsert @idA INT, @idC INT, @datae DATE, @pret FLOAT, @punctaj INT AS
BEGIN
	IF EXISTS(SELECT * FROM CertificariAngajati WHERE idA=@idA AND idC=@idC)
	BEGIN
		UPDATE CertificariAngajati
		SET data_examinarii=@datae, pretul=@pret, punctaj=@punctaj WHERE idA=@idA AND idC=@idC
		PRINT 'CertificariAngajati exista, o actualizam'
	END
	ELSE
	BEGIN
		INSERT INTO CertificariAngajati(idA,idC,data_examinarii,pretul,punctaj) VALUES (@idA,@idC,@datae,@pret,@punctaj)
		PRINT 'CertificariAngajati nu exista, o adaugam'
	END
 END
 GO


-- EXEC Upsert 1,1,'2014-08-09',1000,98   -- actualizare
-- EXEC Upsert 4,1,'2019-04-04',1500,40   -- inserare


-- Certificarea 3 tine de o companie cu rating != [3,5]

GO
CREATE OR ALTER VIEW Vw_Afis2
AS
	SELECT CA.idA, A.nume, A.prenume,A.email, MIN(CA.punctaj) AS Minim, MAX(CA.punctaj) AS Maxim
	FROM CertificariAngajati CA
	INNER JOIN Angajati A ON A.id=CA.idA
	INNER JOIN Certificari C ON C.id=CA.idC
	INNER JOIN Companii CO ON CO.id=C.idC
	WHERE CO.rating>=3 AND CO.rating<=5 
	GROUP BY CA.idA, A.nume,A.prenume,A.email
GO

SELECT * FROM CertificariAngajati

SELECT * FROM Vw_Afis2
