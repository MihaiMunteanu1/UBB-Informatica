CREATE DATABASE Seminar5;

GO
USE Seminar5

CREATE TABLE Persoane
(	cod_p INT NOT NULL,
	nume VARCHAR(100),
	prenume VARCHAR(100),
	data_nasterii DATE,
	localitate VARCHAR(100),
	email VARCHAR(100)
);

INSERT INTO Persoane(cod_p,nume,prenume,data_nasterii,localitate,email) VALUES
(1,'A','Aa','2002-02-12','A','a@yahoo.com'),
(-5,'B','Bb','2003-03-09','B','b@yahoo.com'),
(10,'C','Cc','2004-07-15','C','c@yahoo.com'),
(4,'D','Dd','2005-08-25','D','d@yahoo.com'),
(8,'E','Ee','2006-04-18','E','e@yahoo.com');
INSERT INTO Persoane(cod_p,nume,prenume,data_nasterii,localitate,email) VALUES
(30,'F','Ff','2001-02-12','A','f@yahoo.com');

SELECT * FROM Persoane	
SELECT * FROM Persoane WHERE localitate='A'
SELECT nume,prenume FROM Persoane WHERE localitate='A'

-- daca am cheie primara imi ordoneaza inregistrarile si pe prima pozitie ii cheia
ALTER TABLE Persoane
ADD CONSTRAINT pk_Persoane PRIMARY KEY (cod_p);

INSERT INTO Persoane(cod_p,nume,prenume,data_nasterii,localitate,email) VALUES
(6,'G','Gg','1999-01-12','G','G@yahoo.com');

SELECT * FROM Persoane WHERE cod_p=6
SELECT * FROM Persoane	WHERE localitate='A'


ALTER TABLE Persoane
DROP CONSTRAINT pk_Persoane

-- creare index clustered mod explicit
CREATE CLUSTERED INDEX CIX_Persoane_cod_p_asc ON Persoane (cod_p ASC)

-- daca avem deja index clustered se creeaza non-clustered
ALTER TABLE Persoane
ADD CONSTRAINT pk_Persoane PRIMARY KEY (cod_p);

-- creare index non clustered
CREATE INDEX IX_Persoane_nume_asc_prenume_asc ON Persoane(nume ASC, prenume ASC)

SELECT nume,prenume FROM Persoane WHERE nume='A'

-----------------------------------------------
CREATE TABLE Tari
(	cod_t INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(100)
);

INSERT INTO Tari(nume) VALUES 
('Romania'),('Portugalia'),('Spania');

SELECT * FROM Tari

CREATE UNIQUE INDEX IX_Tari_nume_asc_uq ON TARI (nume);

ALTER TABLE Persoane
ADD CONSTRAINT UQ_email UNIQUE (email);

INSERT INTO Tari(nume) VALUES 
('Anglia'),('Rusia'),('Grecia');

SELECT * FROM Tari

DROP INDEX IX_Tari_nume_asc_uq ON Tari;

CREATE UNIQUE INDEX IX_Tari_nume_asc_uq ON TARI (nume ASC) WITH (IGNORE_DUP_KEY = ON);

INSERT INTO Tari(nume) VALUES 
('Italia'),('Germania'),('Franta');

INSERT INTO Tari(nume) VALUES 
('Italia'),('Germania'),('Franta');

CREATE INDEX IX_Persoane_localitate_asc_email_asc ON Persoane(localitate ASC, email ASC) INCLUDE (prenume);

SELECT prenume, email, localitate FROM Persoane WHERE localitate='A'
SELECT prenume, email, localitate FROM Persoane ORDER BY nume
SELECT prenume, email, localitate FROM Persoane ORDER BY data_nasterii