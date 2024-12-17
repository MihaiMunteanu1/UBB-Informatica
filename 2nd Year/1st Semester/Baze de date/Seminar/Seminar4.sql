CREATE DATABASE Seminar4
USE Seminar4

CREATE TABLE Sectiuni (
	cod_s int primary key identity, 
	nume varchar(100),
	descriere varchar(100));	

CREATE TABLE Atractii(
	cod_a int primary key identity,
	nume varchar(100),
	descriere varchar(100), 
	varsta_min varchar(100),
	cod_s int foreign key references Sectiuni(cod_s));

CREATE TABLE Categorii(
	cod_c int primary key identity,
	nume varchar(100));

CREATE TABLE Vizitatori(
	cod_v int primary key identity,
	nume varchar(100),
	email varchar(100),
	cod_c int foreign key references Categorii(cod_c));

CREATE TABLE Note(
	cod_a int foreign key references Atractii(cod_a),
	cod_v int foreign key references Vizitatori(cod_v),
	nota int,
);

INSERT INTO CATEGORII(nume) VALUES
('Horror'),
('Funny'),
('Adventure'),
('De copii');

INSERT INTO Vizitatori(nume,email,cod_c) VALUES
('Andrei','Albu',1),
('Bogdan','Barbu',1),
('Bubu','Bumbu',1),
('Camil','Chelu',2),
('David','Doru',3),
('Eusebiu','Eu',4),
('Ferent','Feri',4);

INSERT INTO Sectiuni(nume,descriere) VALUES
('S1','S1'),
('S2','S2'),
('S3','S3'),
('S4','S4');

INSERT INTO Atractii(nume,descriere,varsta_min,cod_s) VALUES
('A','A',12,1),
('B','B',12,1),
('C','C',12,2),
('D','D',12,3),
('E','E',12,4);

INSERT INTO NOTE(cod_a,cod_v,nota) VALUES
(1,1,10),
(1,2,8),
(2,3,9),
(2,4,10),
(3,5,7),
(4,6,6),
(5,7,10);

--Ex 1

GO
CREATE FUNCTION CodCategorie(@nume VARCHAR(70))
RETURNS INT AS
BEGIN
	DECLARE @cod_c INT;
	SELECT @cod_c = cod_c
	FROM Categorii
	WHERE nume = @nume

	if @cod_c IS NULL
		Return 0
	Return @cod_c
END;
GO

PRINT dbo.CodCategorie('Horror');

-- Ex 2

GO
CREATE TRIGGER EliminareCategorie
ON Categorii
INSTEAD OF DELETE
AS
BEGIN
	RAISERROR ('operatie interzisa',16,1)
END
GO

DELETE FROM Categorii
SELECT * FROM Categorii

-- Ex 3

GO
CREATE VIEW vw_CategoriiFunnyHorror
AS
SELECT C.cod_c, C.nume
FROM Categorii C
WHERE C.nume IN ('Funny','Horror')
GO

SELECT * FROM vw_CategoriiFunnyHorror

-- Ex 4

GO
CREATE VIEW vw_SectiuniIncepCuS
AS
SELECT S.cod_s, S.nume
FROM Sectiuni S
WHERE S.nume LIKE 'S%'
GO

SELECT * FROM vw_SectiuniIncepCuS


-- Ex 5		
GO
CREATE OR ALTER FUNCTION fn_SectiuniCuLitera(@litera CHAR(1))
RETURNS TABLE
AS
RETURN
(
    SELECT S.cod_s, S.nume
    FROM Sectiuni S
    --WHERE LEN(nume) >= 2 AND nume LIKE '%' + @litera
	WHERE nume LIKE '_%' + @litera
);
GO

SELECT * FROM fn_SectiuniCuLitera('1');

	
-- Ex 6

GO
CREATE OR ALTER VIEW vw_VizitatoriNoteAtractii
AS
SELECT 
    V.nume AS NumeVizitator,
    N.nota AS Nota,
    A.nume AS NumeAtractie
FROM Vizitatori V
INNER JOIN Note N ON V.cod_v = N.cod_v
INNER JOIN Atractii A ON N.cod_a = A.cod_a;
GO

SELECT * FROM vw_VizitatoriNoteAtractii;

