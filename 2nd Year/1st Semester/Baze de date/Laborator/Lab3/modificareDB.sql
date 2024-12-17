USE LLAB2;


--Modificare tipul unei coloane
GO
CREATE PROCEDURE versiune1
AS
BEGIN
	ALTER TABLE Eveniment
	ALTER COLUMN descriere VARCHAR(50);
END
GO

EXEC versiune1

GO
CREATE PROCEDURE versiuneInvers1
AS
BEGIN
	ALTER TABLE Eveniment
	ALTER COLUMN descriere VARCHAR(200);
END
GO

EXEC versiuneInvers1

--Adauga constrangere
GO
CREATE PROCEDURE versiune2
AS
BEGIN
	ALTER TABLE Locatie 
	ADD CONSTRAINT DF_Locatie_Capacitate DEFAULT 150 FOR capacitate;
END
GO

EXEC versiune2

GO
CREATE PROCEDURE versiuneInvers2
AS
BEGIN
	ALTER TABLE Locatie DROP CONSTRAINT DF_Locatie_Capacitate;
END
GO

EXEC versiuneInvers2

-- Creare unei tabele noi
GO
CREATE PROCEDURE versiune3
AS
BEGIN
	CREATE TABLE Fotograf (
		id_fotograf INT PRIMARY KEY IDENTITY(1,1),
		id_eveniment INT NOT NULL,
		nume VARCHAR(100) NOT NULL,
		prenume VARCHAR(100) NOT NULL,
		experienta INT NOT NULL
	);
END
GO

EXEC versiune3

GO
CREATE PROCEDURE versiuneInvers3
AS
BEGIN
	DROP TABLE Fotograf;
END
GO

EXEC versiuneInvers3

-- Adaugarea unui camp nou
GO
CREATE PROCEDURE versiune4
AS
BEGIN
	ALTER TABLE Clienti 
	ADD email VARCHAR(100);
END
GO

EXEC versiune4

GO
CREATE PROCEDURE versiuneInvers4
AS
BEGIN
	ALTER TABLE Clienti 
	DROP COLUMN email;
END
GO

EXEC versiuneInvers4

-- Creare o constrangere de cheie straina
GO
CREATE PROCEDURE versiune5
AS
BEGIN
	ALTER TABLE Fotograf 
	ADD CONSTRAINT FK_Fotograf_Eveniment 
	FOREIGN KEY (id_eveniment) REFERENCES Eveniment(id_eveniment) ON UPDATE CASCADE ON DELETE CASCADE;
END
GO

EXEC versiune5

GO
CREATE PROCEDURE versiuneInvers5
AS
BEGIN
	ALTER TABLE Fotograf 
	DROP CONSTRAINT FK_Fotograf_Eveniment;
END
GO

EXEC versiuneInvers5

-- Tabela pentru memorarea versiunii structurii de baza
CREATE TABLE VersiuneDB (
	cod_v INT PRIMARY KEY IDENTITY,
	nr_versiune INT
);

INSERT INTO VersiuneDB (nr_versiune) VALUES(0);

-- Procedura principala 
GO
CREATE OR ALTER PROCEDURE main @versiune INT
AS
BEGIN
	IF @versiune < 0 OR @versiune > 5
	BEGIN
		PRINT 'Versiune invalida'
		RETURN
	END

	DECLARE @versiune_curenta AS INT
	SET @versiune_curenta = (SELECT nr_versiune FROM VersiuneDB)

	IF @versiune = @versiune_curenta
	BEGIN
		PRINT 'Versiunea actuala este deja cea curenta'
		RETURN
	END

	-- Variabile pentru proceduri
	DECLARE @proc VARCHAR(30)
	DECLARE @proc_undo VARCHAR(30)
	DECLARE @ok AS INT
	SET @ok = 0

	-- Actualizare versiune in tabela 'VersiuneDB'
	DELETE FROM VersiuneDB
	INSERT INTO VersiuneDB(nr_versiune) VALUES (@versiune)

	WHILE(@versiune_curenta < @versiune)
	BEGIN
		SET @ok = @ok + 1
		SET @versiune_curenta = @versiune_curenta + 1
		SET @proc = 'versiune' + CAST(@versiune_curenta AS VARCHAR(10))
		PRINT 'Se executa ' + @proc
		EXEC @proc
	END

	IF(@ok > 0)
	BEGIN
		RETURN
	END

	WHILE(@versiune_curenta > @versiune)
	BEGIN
		SET @proc_undo = 'versiuneInvers' + CAST(@versiune_curenta AS VARCHAR(10))
		PRINT 'Se executa ' + @proc_undo
		EXEC @proc_undo
		SET @versiune_curenta = @versiune_curenta - 1
	END
END
GO

EXEC main @versiune=0;
EXEC main @versiune=1;
EXEC main @versiune=2;
EXEC main @versiune=3;
EXEC main @versiune=4;
EXEC main @versiune=5;

SELECT * FROM VersiuneDB
