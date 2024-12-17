USE LLAB2;

-- Tabele: Eveniment - Eveniment Clienti - Clienti 
--                   - Eveniment DJ - DJ



-- validare id eveniment
GO 
CREATE OR ALTER FUNCTION ValidateEvenimentID(@id INT) RETURNS BIT AS
BEGIN
	IF(NOT EXISTS (SELECT * FROM Eveniment WHERE id_eveniment=@id))
		BEGIN
			RETURN 0
		END
	RETURN 1
END
GO

-- validare campurilor Evenimentului
GO
CREATE OR ALTER FUNCTION ValidateEveniment(@nume VARCHAR(100), @data_eveniment DATE ) RETURNS BIT AS
BEGIN
	
	IF(@nume = NULL)
	BEGIN
		RETURN 0
	END
	IF(LEN(@nume) < 3)
	BEGIN
		RETURN 0
	END

	IF(@data_eveniment = NULL)
	BEGIN
		RETURN 0
	END

	RETURN 1
END

--validare id client
GO 
CREATE OR ALTER FUNCTION ValidateClientID(@id INT) RETURNS BIT AS
BEGIN
	IF(NOT EXISTS (SELECT * FROM Clienti WHERE id_client=@id))
		BEGIN
			RETURN 0
		END
	RETURN 1
END
GO

-- validare daca mai sunt locuri libere la masa
GO
CREATE OR ALTER FUNCTION VerificaLocuriLibere(@id_masa INT) RETURNS INT 
AS
BEGIN
    DECLARE @locuri_totale INT;
    DECLARE @locuri_ocupate INT;
    DECLARE @locuri_libere INT;

    -- Obține numărul total de locuri la masă
    SELECT @locuri_totale = locuri
    FROM Mese
    WHERE id_masa = @id_masa;

    -- Obține numărul de locuri ocupate la masă
    SELECT @locuri_ocupate = COUNT(*)
    FROM Clienti
    WHERE id_masa = @id_masa;

    -- Calculează locurile libere
    IF @locuri_totale IS NOT NULL
        SET @locuri_libere = @locuri_totale - @locuri_ocupate;
    ELSE
        SET @locuri_libere = 0; -- Masa nu există

    RETURN @locuri_libere;
END;


--validare campurile client
GO
CREATE OR ALTER FUNCTION ValidateClient(@id_m INT, @nume VARCHAR(100), @prenume VARCHAR(100)) RETURNS BIT AS
BEGIN
	if(NOT EXISTS ( SELECT * FROM Mese WHERE id_masa=@id_m))
	BEGIN
		RETURN 0
	END

	IF( dbo.VerificaLocuriLibere(@id_m) = 0)
	BEGIN
		RETURN 0
	END

	IF(@nume IS NULL)
	BEGIN 
		RETURN 0
	END

	IF(@prenume IS NULL)
	BEGIN 
		RETURN 0
	END

	RETURN 1
END


--validare EvenimentCLIENTI
GO
CREATE OR ALTER FUNCTION ValidateEvenimentClienti(@id_e INT ,@id_c INT,@buget_de_cheltuit INT) RETURNS BIT AS
BEGIN
	IF(NOT EXISTS (SELECT id_eveniment,id_client FROM Eveniment_Clienti WHERE id_eveniment=@id_e AND id_client=@id_c))
	BEGIN
		RETURN 0
	END

	IF(@buget_de_cheltuit < 0)
	BEGIN
		RETURN 0
	END

	RETURN 1
END

--validare EvenimentCLIENTI - ID
GO
CREATE OR ALTER FUNCTION ValidateEvenimentClientiID(@id_e INT ,@id_c INT) RETURNS BIT AS
BEGIN
	IF(NOT EXISTS (SELECT id_eveniment,id_client FROM Eveniment_Clienti WHERE id_eveniment=@id_e AND id_client=@id_c))
	BEGIN
		RETURN 0
	END


	RETURN 1
END


--validare id DJ
GO 
CREATE OR ALTER FUNCTION ValidateDJID(@id INT) RETURNS BIT AS
BEGIN
	IF(NOT EXISTS (SELECT * FROM DJ WHERE id_dj=@id))
	BEGIN
		RETURN 0
	END
	RETURN 1
END
GO

-- validare campuri DJ
GO 
CREATE OR ALTER FUNCTION ValidateDJ(@nume VARCHAR(50), @prenume VARCHAR(50),@gen_muzica VARCHAR(50), @experienta INT) RETURNS BIT AS
BEGIN
	if(@nume IS NULL)
	BEGIN 
		RETURN 0
	END

	if(@prenume IS NULL)
	BEGIN 
		RETURN 0
	END

	IF(@experienta  IS NULL)
	BEGIN
		RETURN 0
	END

	IF(EXISTS (SELECT gen_muzica FROM DJ WHERE gen_muzica=@gen_muzica))
	BEGIN
		RETURN 0
	END

	RETURN 1
END

-- validare Eveniment DJ
GO
CREATE OR ALTER FUNCTION ValidateEvenimentDJ(@id_e INT,@id_dj INT,@plata INT) RETURNS BIT AS
BEGIN
	IF(NOT EXISTS(SELECT * FROM Eveniment_DJ WHERE @id_e = id_eveniment AND @id_dj=id_dj))
	BEGIN
		RETURN 0
	END

	IF(@plata<0)
	BEGIN
		RETURN 0
	END

	RETURN 1
END

-- validare Eveniment DJ - ID
GO
CREATE OR ALTER FUNCTION ValidateEvenimentDJID(@id_e INT,@id_dj INT) RETURNS BIT AS
BEGIN
	IF(NOT EXISTS(SELECT * FROM Eveniment_DJ WHERE @id_e = id_eveniment AND @id_dj=id_dj))
	BEGIN
		RETURN 0
	END

	RETURN 1
END

-----------------------------------

-- create Eveniment
GO
CREATE OR ALTER PROCEDURE CreateEveniment (@nume VARCHAR(100),@data_e DATE, @descriere VARCHAR(200)) AS
BEGIN
	IF (dbo.ValidateEveniment(@nume,@data_e) = 1)
	BEGIN
		INSERT INTO Eveniment(nume,data_eveniment,descriere) VALUES
			(@nume,@data_e,@descriere)
		PRINT 'Eveniment adaugat cu succes.'
	END
	ELSE
	BEGIN
		PRINT 'Datele Evenimentului sunt invalide.' + CHAR(10) +
			  'Nume -> must not be null and has to have more than 3 characters' + CHAR(10) +
			  'Data -> must not be null'
	END

END
GO

-- read Eveniment
GO
CREATE OR ALTER PROCEDURE ReadEveniment(@id_e INT) AS
BEGIN
	IF(dbo.ValidateEvenimentID(@id_e) = 1)
	BEGIN
		SELECT * FROM Eveniment WHERE id_eveniment=@id_e
	END
	ELSE
	BEGIN
		PRINT 'Evenimentul nu exista'
	END
END
GO

-- update Eveniment
GO
CREATE OR ALTER PROCEDURE UpdateEveniment(@id INT,@nume VARCHAR(100),@data_e DATE, @descriere VARCHAR(200)) AS
BEGIN
	IF(dbo.ValidateEvenimentID(@id) = 0) 
	BEGIN
		PRINT 'Evenimentul nu exista'
	END

	IF(dbo.ValidateEveniment(@nume,@data_e) = 1)
	BEGIN
		UPDATE Eveniment
		SET nume=@nume,data_eveniment=@data_e ,descriere=@descriere
		WHERE id_eveniment=@id

		PRINT 'Eveniment actualizat cu succes'
	END
	ELSE
	BEGIN
		PRINT 'Datele Evenimentului sunt invalide.' + CHAR(10) +
			  'Nume -> must not be null and has to have more than 3 characters' + CHAR(10) +
			  'Data -> must not be null'
	END
END
GO

-- delete Eveniment
GO
CREATE OR ALTER PROCEDURE DeleteEveniment(@id INT) AS
BEGIN
	IF(dbo.ValidateEvenimentID(@id) = 1)
	BEGIN
		DELETE FROM Eveniment WHERE id_eveniment=@id
		PRINT 'Eveniment sters cu succes'
	END
	ELSE
	BEGIN
		PRINT 'Evenimentul nu exista'
	END
END
GO


----------------------------------------------------------



-- create Client
GO
CREATE OR ALTER PROCEDURE CreateClient (@id_masa INT ,@nume VARCHAR(100), @prenume VARCHAR(100)) AS
BEGIN
	IF (dbo.ValidateClient(@id_masa,@nume,@prenume) = 1)
	BEGIN
		INSERT INTO Clienti(id_masa,nume,prenume) VALUES
			(@id_masa,@nume,@prenume)
		PRINT 'Client adaugat cu succes.'
	END
	ELSE
	BEGIN
		PRINT 'Datele Clientului sunt invalide.' + CHAR(10) +
		      'id_masa -> must not be null or the table has to exists' + CHAR(10) +
			  'nume -> must not be null' + CHAR(10) +
			  'prenume -> must not be null' + CHAR(10) + 
			  'sau' + CHAR(10) + 
			  'NU mai sunt locuri libere la acea masa'
	END
END
GO

-- create DJ
GO
CREATE OR ALTER PROCEDURE CreateDJ (@nume VARCHAR(100), @prenume VARCHAR(100),@gen_muzica VARCHAR(100),@experienta INT) AS
BEGIN
	IF (dbo.ValidateDJ(@nume,@prenume,@gen_muzica,@experienta) = 1)
	BEGIN
		INSERT INTO DJ(nume,prenume,gen_muzica,experienta) VALUES (@nume,@prenume,@gen_muzica,@experienta)
		PRINT 'DJ adaugat cu succes.'
	END
	ELSE
	BEGIN
		PRINT 'Datele DJ-ului sunt invalide.' + CHAR(10) + 
		      ' nume -> must not be null' + CHAR(10) + 
			  ' prenume -> must not be null ' + CHAR(10) +
			  ' gen_muzica -> must not be null and has to be unique' + CHAR(10) +
			  ' experienta -> must not be null'	
	END
END
GO

-- create EvenimentClienti
GO
CREATE OR ALTER PROCEDURE CreateEvenimentClient (@id_e INT, @id_c INT,@buget INT) AS
BEGIN
	IF (dbo.ValidateEvenimentID(@id_e) = 1 AND dbo.ValidateClientID(@id_c) = 1 AND 
		dbo.ValidateEvenimentClienti(@id_e,@id_c,@buget) = 0 )
	BEGIN
		INSERT INTO Eveniment_Clienti(id_eveniment,id_client,buget_de_cheltuit) VALUES (@id_e,@id_c,@buget)		
		PRINT 'Client adaugat cu succes la eveniment.'

	END
	ELSE
	BEGIN
		PRINT 'Datele evenimentului sau ale clientului sunt invalide.' + CHAR(10) +
			  'id_eveniment -> must not be null and the Eveniment has to exists' + CHAR(10)+
			  'id_client -> must not be null and the Client has to exists' + CHAR(10) +
			  'buget_de_cheltuit -> must not be null or lower than 0' +CHAR(10) +
			  'Clientul poate sa participe/sa fi fost participat la acest eveniment'
	END
END
GO

-- create EvenimentDj
GO
CREATE OR ALTER PROCEDURE CreateEvenimentDJ (@id_e INT, @id_dj INT,@plata INT) AS
BEGIN
	IF (dbo.ValidateEvenimentID(@id_e) = 1 AND dbo.ValidateDJID(@id_dj) = 1 AND 
		dbo.ValidateEvenimentDJ(@id_e,@id_dj,@plata) = 0 )
	BEGIN
		INSERT INTO Eveniment_DJ(id_eveniment,id_dj,plata) VALUES (@id_e,@id_dj,@plata)
		PRINT 'DJ adaugat cu succes la eveniment.'
	END
	ELSE
	BEGIN
		PRINT 'Datele evenimentului sau ale dj-ului sunt invalide.' + CHAR(10) +
			  'id_eveniment -> must not be null and the Eveniment has to exists' + CHAR(10)+
			  'id_dj -> must not be null and the DJ has to exists' + CHAR(10) +
			  'plata -> must not be null and must be greater than 0' + CHAR(10) +
			  'DJ poate sa mixeze/a mixat la acest eveniment'
	END
END
GO

--------------------------------------


-- read Client
GO
CREATE OR ALTER PROCEDURE ReadClient(@id_c INT) AS
BEGIN
	IF(dbo.ValidateClientID(@id_c) = 1)
	BEGIN
		SELECT * FROM Clienti WHERE id_client=@id_c
	END
	ELSE
	BEGIN
		PRINT 'Clientul nu exista'
	END
END
GO

-- read DJ
GO
CREATE OR ALTER PROCEDURE ReadDJ(@id_dj INT) AS
BEGIN
	IF(dbo.ValidateDJID(@id_dj) = 1)
	BEGIN
		SELECT * FROM DJ WHERE id_dj=@id_dj
	END
	ELSE
	BEGIN
		PRINT 'DJ-ul nu exista'
	END
END
GO

-- read EvenimentClient
GO
CREATE OR ALTER PROCEDURE ReadEvenimentClient(@id_e INT, @id_c INT) AS
BEGIN
	IF(dbo.ValidateEvenimentClientiID(@id_e,@id_c) = 1)
	BEGIN
		SELECT * FROM Eveniment_Clienti WHERE id_eveniment=@id_e AND id_client=@id_c
	END
	ELSE
	BEGIN
		PRINT 'Eroare: ' + CHAR(10) +
			  'Evenimentul nu exista' + CHAR(10) + 'sau' + CHAR(10) +
			  'Clientul nu exista' + CHAR(10) + 'sau' + CHAR(10) +
			  'Clientul nu participa la acest eveniment'
	END
END
GO

-- read EvenimentDJ
GO
CREATE OR ALTER PROCEDURE ReadEvenimentDJ(@id_e INT, @id_dj INT) AS
BEGIN
	IF(dbo.ValidateEvenimentDJID(@id_e,@id_dj) = 1)
	BEGIN
		SELECT * FROM Eveniment_DJ WHERE id_eveniment=@id_e AND id_dj=@id_dj
	END
	ELSE
	BEGIN
		PRINT 'Eroare: ' + CHAR(10) +
			  'Evenimentul nu exista' + CHAR(10) + 'sau' + CHAR(10) +
			  'DJ-ul nu exista' + CHAR(10) + 'sau' + CHAR(10) +
			  'DJ-ul nu mixeaza la acest eveniment'
	END
END
GO

-----------------------------------------------------------------------------------


-- update Client
GO
CREATE OR ALTER PROCEDURE UpdateClient(@id INT,@id_masa INT,@nume VARCHAR(100),@prenume VARCHAR(100)) AS
BEGIN
	IF(dbo.ValidateClientID(@id) = 0) 
	BEGIN
		PRINT 'Clientul nu exista'
	END

	IF(dbo.ValidateClient(@id_masa,@nume,@prenume) = 1)
	BEGIN
		UPDATE Clienti
		SET  id_masa=@id_masa, nume=@nume, prenume=@prenume
		WHERE id_client=@id

		PRINT 'Client actualizat cu succes'
	END
	ELSE
	BEGIN
		PRINT 'Datele Clientului sunt invalide.' + CHAR(10) +
		      'id_masa -> must not be null or the table has to exists' + CHAR(10) +
			  'nume -> must not be null' + CHAR(10) +
			  'prenume -> must not be null' + CHAR(10) +
			  'sau' + CHAR(10) + 
			  'NU mai sunt locuri libere la acea masa'
	END
END
GO


-- update DJ
GO
CREATE OR ALTER PROCEDURE UpdateDJ(@id INT,@nume VARCHAR(100),@prenume VARCHAR(100),@gen_muzica VARCHAR(100),@experienta INT) 
AS
BEGIN
	IF(dbo.ValidateDJID(@id) = 0) 
	BEGIN
		PRINT 'DJ-ul nu exista'
	END

	IF(dbo.ValidateDJ(@nume,@prenume,@gen_muzica,@experienta) = 1)
	BEGIN
		UPDATE DJ
		SET  nume=@nume, prenume=@prenume, gen_muzica=@gen_muzica, experienta=@experienta
		WHERE id_dj=@id

		PRINT 'DJ-ul actualizat cu succes'
	END
	ELSE
	BEGIN
		PRINT 'Datele DJ-ului sunt invalide.' + CHAR(10) + 
		      ' nume -> must not be null' + CHAR(10) + 
			  ' prenume -> must not be null ' + CHAR(10) +
			  ' gen_muzica -> must not be null and has to be unique' + CHAR(10) +
			  ' experienta -> must not be null'	
	END
END
GO


-- update EvenimentClient
GO
CREATE OR ALTER PROCEDURE UpdateEvenimentClient(@id_e INT,@id_c INT, @newBuget INT) 
AS
BEGIN

	IF(dbo.ValidateEvenimentID(@id_e) = 0)
	BEGIN
		PRINT 'Evenimentul de actualizat nu exista'
	END

	IF(dbo.ValidateClientID(@id_c) = 0)
	BEGIN
		PRINT 'Clientul de actualizat nu exista'
	END

	IF(dbo.ValidateEvenimentClienti(@id_e,@id_c,@newBuget) = 1 )
	BEGIN
		UPDATE Eveniment_Clienti
		SET  buget_de_cheltuit=@newBuget
		WHERE id_client=@id_c and id_eveniment=@id_e

		PRINT 'Clientul la acest Eveniment s-a actualizat cu succes'
	END
	ELSE
	BEGIN
		PRINT 'Eroare: ' + CHAR(10) +
			  'Evenimentul nou nu exista' + CHAR(10) + 'sau' + CHAR(10) +
			  'Clientul nou nu exista' + CHAR(10) + 'sau' + CHAR(10) +
			  'Plata este mai mica ca 0' +CHAR(10) + 'sau' + CHAR(10) +
			  'Clientul nou participa/va participa la acest eveniment'
	END
END
GO

-- update EvenimentDJ
GO
CREATE OR ALTER PROCEDURE UpdateEvenimentDJ(@id_e INT,@id_dj INT, @newPlata INT) 
AS
BEGIN

	IF(dbo.ValidateEvenimentID(@id_e) = 0)
	BEGIN
		PRINT 'Evenimentul de actualizat nu exista'
	END

	IF(dbo.ValidateDJID(@id_dj) = 0)
	BEGIN
		PRINT 'DJ-ul de actualizat nu exista'
	END

	IF(dbo.ValidateEvenimentDJ(@id_e,@id_dj,@newPlata) = 1)
	BEGIN
		UPDATE Eveniment_DJ
		SET  plata = @newPlata
		WHERE id_dj=@id_dj and id_eveniment=@id_e

		PRINT 'EvenimentDJ actualizat cu succes'
	END
	ELSE
	BEGIN
		PRINT 'Datele evenimentului sau ale dj-ului sunt invalide.' + CHAR(10) +
			  'new id_eveniment -> must not be null and the Eveniment has to exists' + CHAR(10)+
			  'new id_dj -> must not be null and the DJ has to exists' + CHAR(10) +
			  'plata -> must not be null and lower than 0' + CHAR(10) +
			  'DJ poate sa mixeze/a mixat la acest eveniment'
	END
END
GO

--------------------------------------------------------------



-- delete Client
GO
CREATE OR ALTER PROCEDURE DeleteClient(@id INT) AS
BEGIN
	IF(dbo.ValidateClientID(@id) = 1)
	BEGIN
		DELETE FROM Clienti WHERE id_client=@id
		PRINT 'Client sters cu succes'
	END
	ELSE
	BEGIN
		PRINT 'Clientul nu exista'
	END
END
GO

-- delete DJ
GO
CREATE OR ALTER PROCEDURE DeleteDJ(@id INT) AS
BEGIN
	IF(dbo.ValidateDJID(@id) = 1)
	BEGIN
		DELETE FROM DJ WHERE id_dj=@id
		PRINT 'DJ sters cu succes'
	END
	ELSE
	BEGIN
		PRINT 'DJ-ul nu exista'
	END
END
GO

-- delete EvenimentClient
GO
CREATE OR ALTER PROCEDURE DeleteEvenimentClient(@id_e INT,@id_c INT) AS
BEGIN
	IF(dbo.ValidateEvenimentClientiID(@id_e,@id_c) = 1)
	BEGIN
		DELETE FROM Eveniment_Clienti WHERE id_eveniment=@id_e AND id_client=@id_c
		PRINT 'S-a sters cu succes clientul de la eveniment'
	END
	ELSE
	BEGIN
		PRINT 'Nu exista acest client la acest eveniment'
	END
END
GO

-- delete EvenimentDJ
GO
CREATE OR ALTER PROCEDURE DeleteEvenimentDJ(@id_e INT,@id_dj INT) AS
BEGIN
	IF(dbo.ValidateEvenimentDJID(@id_e,@id_dj) = 1)
	BEGIN
		DELETE FROM Eveniment_DJ WHERE id_eveniment=@id_e AND id_dj=@id_dj
		PRINT 'S-a sters cu succes dj-ul de la eveniment'
	END
	ELSE
	BEGIN
		PRINT 'Nu exista acest dj la acest eveniment'
	END
END
GO
------------------------------------------------------------
DBCC CHECKIDENT ('Eveniment', RESEED, 8);
DBCC CHECKIDENT ('DJ', RESEED, 3);
DBCC CHECKIDENT ('Clienti', RESEED, 84);



-------------------------------------------------------------
-- Test CRUD pentru Eveniment

EXEC CreateEveniment 'EvenimentCRU','2026-01-01','Descriere'

SELECT * FROM Eveniment

EXEC ReadEveniment 9

EXEC UpdateEveniment 9,'EvenimentCrudUPDATE','2026-02-02','Descriere2'

EXEC ReadEveniment 9

EXEC DeleteEveniment 9

EXEC ReadEveniment 9
SELECT * FROM Eveniment


-- Test CRUD pentru Clienti
--ex: masa cu id: 7 e plina

EXEC CreateClient 1,'ClientCRUD1','ClientCRUD1'

SELECT * FROM Clienti

EXEC ReadClient 85

EXEC UpdateClient 85,1,'ClientCRUD1Update','ClientCRUD1Update'

EXEC ReadClient 85

EXEC DeleteClient 85

EXEC ReadClient 85

-- Test CRUD pentru DJ

EXEC CreateDJ 'DJCrud1','DJCRUD1','afro',10

SELECT * FROM DJ

EXEC ReadDJ 4

EXEC UpdateDJ 4,'DJCrud1Update','DJCRUD1Update','techno',5

EXEC ReadDJ 4

EXEC DeleteDJ 4

EXEC ReadDJ 4

-- Test CRUD pentru EvenimentClient

EXEC CreateEvenimentClient 2,1,300

SELECT * FROM Eveniment_Clienti

EXEC ReadEvenimentClient 2,1

EXEC UpdateEvenimentClient 2,1,500

EXEC ReadEvenimentClient 2,1

EXEC DeleteEvenimentClient 2,1

EXEC ReadEvenimentClient 2,1


-- Test CRUD pentru EvenimentDJ

EXEC CreateEvenimentDJ 1,3,1000

SELECT * FROM Eveniment_DJ

EXEC ReadEvenimentDJ 1,3

EXEC UpdateEvenimentDJ 1,3,5555

EXEC ReadEvenimentDJ 1,3

EXEC DeleteEvenimentDJ 1,3

EXEC ReadEvenimentDJ 1,3



---------------------------------------------------------------
-- View: Evenimentele sortate dupa data lor
GO
CREATE OR ALTER VIEW View_Evenimente_Data 
AS
	SELECT E.id_eveniment,E.nume,E.data_eveniment,E.descriere
	FROM Eveniment E
GO


-- Index pentru View_Evenimente_Data
GO
CREATE NONCLUSTERED INDEX IX_Evenimente_Data ON Eveniment (data_eveniment ASC);
GO

SELECT * FROM View_Evenimente_Data
ORDER BY data_eveniment

-----------------------

-- View: DJ ordonati descrescator dupa ani de experienta
GO
CREATE OR ALTER VIEW View_DJ_Experienta AS
	SELECT dj.id_dj, dj.nume AS Nume_DJ, dj.prenume AS Prenume_DJ, dj.experienta
	FROM DJ dj
GO

-- Index pentru View_DJ_Experienta
GO
CREATE NONCLUSTERED INDEX IX_DJ_Experienta ON DJ (experienta DESC);
GO

SELECT * FROM View_DJ_Experienta
ORDER BY experienta ASC

