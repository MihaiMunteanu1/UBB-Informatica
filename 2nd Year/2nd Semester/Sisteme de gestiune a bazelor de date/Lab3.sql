USE LLAB2;

-- Eveniment - EvenimentDJ - DJ

-- Sistem de logare
CREATE TABLE LoggingTable
(
	id INT PRIMARY KEY IDENTITY(1, 1),
	operationType VARCHAR(50),
	tableName VARCHAR(50),
	executionTime DATETIME
);

-- Eveniment(nume, data eveniment, descriere)
-- functie de validare pentru data
GO
CREATE OR ALTER FUNCTION IsValidDateFormat (@DateValue VARCHAR(10))
RETURNS BIT
AS
BEGIN
    DECLARE @ok BIT = 0;
    IF ISDATE(@DateValue) = 1
	BEGIN
        SET @ok = 1;
    END
	RETURN @ok;
END;
GO

--DJ(nume,prenume,gen_muzica,experienta)
-- functie de validare pentru gen_muzica
GO
CREATE OR ALTER FUNCTION IsValidGenMuzica(@GenMuzica VARCHAR(30))
RETURNS BIT
AS
BEGIN
    DECLARE @ok BIT = 0;
    IF @GenMuzica IN ('Rap','Trap','Hip-Hop','Pop','R&B','Rock')
        SET @ok = 1;
    RETURN @ok;
END;
GO

--Functie de validare pentru Eveniment
GO
CREATE OR ALTER FUNCTION ValidateEveniment2(
	@nume VARCHAR(100), 
	@data_eveniment DATE,
	@descriere VARCHAR(200)
)
RETURNS VARCHAR(300)
AS 
BEGIN
	DECLARE @errors VARCHAR(300)
	SET @errors = ''
	IF( @nume IS NULL OR @nume='')
	BEGIN
		SET @errors = @errors + 'Nume Eveniment invalid! ' 
	END

	IF(@data_eveniment IS NULL OR dbo.IsValidDateFormat(CONVERT(VARCHAR(10), @data_eveniment, 120)) = 0)
	BEGIN
		SET @errors = @errors + 'Data Eveniment invalid! ' 
	END

	RETURN @errors
END
GO

--Functie de validare pentru DJ
GO
CREATE OR ALTER FUNCTION ValidateDJ2(
	@nume VARCHAR(100), 
	@prenume VARCHAR(100),
	@gen_muzica VARCHAR(100),
	@experienta INT
)
RETURNS VARCHAR(300)
AS 
BEGIN
	DECLARE @errors VARCHAR(300)
	SET @errors = ''
	IF( @nume IS NULL OR @nume='')
	BEGIN
		SET @errors = @errors + 'Nume DJ invalid! ' 
	END
	IF( @prenume IS NULL OR @prenume='')
	BEGIN
		SET @errors = @errors + 'Prenume DJ invalid! ' 
	END
	IF( @gen_muzica IS NULL OR @gen_muzica='' OR dbo.IsValidGenMuzica(@gen_muzica) = 0)
	BEGIN
		SET @errors = @errors + 'GenMuzica DJ invalid! ' 
	END
	IF( @experienta IS NULL OR @experienta<0)
	BEGIN
		SET @errors = @errors + 'Experienta DJ invalid! ' 
	END
	RETURN @errors
END
GO

--Functie de validare pentru Eveniment_DJ
GO
CREATE OR ALTER FUNCTION ValidateEvenimentDJ2(
	@id_eveniment INT,
	@id_dj INT,
	@plata INT
)
RETURNS VARCHAR(300)
AS 
BEGIN
	DECLARE @errors VARCHAR(300)
	SET @errors = ''
	IF (EXISTS(SELECT * FROM Eveniment_DJ WHERE @id_eveniment = id_eveniment AND @id_dj=id_dj))
	BEGIN
		SET @errors = @errors + 'DJ-ul participa deja la eveniment! ' 
	END

	IF( @id_eveniment IS NULL OR @id_eveniment<0)
	BEGIN
		SET @errors = @errors + 'ID_Eveniment invalid! ' 
	END
	ELSE IF(NOT EXISTS (SELECT * FROM Eveniment WHERE id_eveniment=@id_eveniment))
	BEGIN
		SET @errors = @errors + 'Evenimentul nu exista! ' 
	END

	IF( @id_dj IS NULL OR @id_dj<0)
	BEGIN
		SET @errors = @errors + 'ID_DJ invalid! ' 
	END
	ELSE IF(NOT EXISTS (SELECT * FROM DJ WHERE id_dj=@id_dj))
	BEGIN
		SET @errors = @errors + 'DJ-ul nu exista! ' 
	END

	IF( @plata IS NULL OR @plata<0)
	BEGIN
		SET @errors = @errors + 'Plata dj invalid! ' 
	END
	RETURN @errors
END;
GO

-----------------------------------------------------------------
--ex 1
GO
CREATE OR ALTER PROCEDURE InsertData
(
	@numeE VARCHAR(100),
	@data_e DATE,
	@descriere VARCHAR(200),

	@numeDJ VARCHAR(100),
	@prenumeDJ VARCHAR(100),
	@gen_muzica VARCHAR(100),
	@experienta INT,

	@plata INT
)
AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		DECLARE @errorMessage VARCHAR(300)

		-- validare Eveniment
		SET @errorMessage = dbo.ValidateEveniment2(@numeE, @data_e, @descriere)
		IF (@errorMessage != '')
		BEGIN
			PRINT 'Error Eveniment: ' + @errorMessage
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO Eveniment(nume, data_eveniment, descriere)
		VALUES (@numeE, @data_e, @descriere)
		
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('INSERT', 'Eveniment', CURRENT_TIMESTAMP)

		-- validare DJ
		SET @errorMessage = dbo.ValidateDJ2(@numeDJ, @prenumeDJ, @gen_muzica, @experienta)
		IF (@errorMessage != '')
		BEGIN
			PRINT 'Error DJ: ' + @errorMessage
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO DJ(nume, prenume, gen_muzica, experienta)
		VALUES (@numeDJ, @prenumeDJ, @gen_muzica, @experienta)
		
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('INSERT', 'DJ', CURRENT_TIMESTAMP)

		-- obtinem id-urile
		DECLARE @insertedIdEveniment INT = (SELECT MAX(id_eveniment) FROM Eveniment)
		DECLARE @insertedIdDJ INT = (SELECT MAX(id_dj) FROM DJ)

		-- validare Eveniment_DJ
		SET @errorMessage = dbo.ValidateEvenimentDJ2(@insertedIdEveniment, @insertedIdDJ, @plata)
		IF (@errorMessage != '')
		BEGIN
			PRINT 'Error Eveniment_DJ: ' + @errorMessage
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO Eveniment_DJ(id_eveniment, id_dj, plata)
		VALUES (@insertedIdEveniment, @insertedIdDJ, @plata)
		
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('INSERT', 'Eveniment_DJ', CURRENT_TIMESTAMP)

		COMMIT TRAN

		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('TRANSACTION COMMITTED', 'AllTables', CURRENT_TIMESTAMP)
		SELECT 'Transaction committed'
	END TRY

	BEGIN CATCH
		ROLLBACK TRAN
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('TRANSACTION ROLLBACKED', 'AllTables', CURRENT_TIMESTAMP)
		SELECT 'Transaction rollbacked'
	END CATCH
END
GO

-- executie cu succes
EXEC InsertData 
	@numeE = 'BeachPlease2',
	@data_e = '2025-07-09',
	@descriere =  NULL,
	
	@numeDJ = 'Metro',
	@prenumeDJ = 'Boomin',
	@gen_muzica = 'Rap',
	@experienta = 15,
	
	@plata = 100000;

SELECT * FROM Eveniment;
SELECT * FROM DJ;
SELECT * FROM Eveniment_DJ;
SELECT * FROM LoggingTable;

-- executie cu eroare
EXEC InsertData 
	@numeE = 'BeachPlease22',
	@data_e = '2025-07-13',
	@descriere = 'aa',

	@numeDJ = 'Travis',
	@prenumeDJ = 'Scott',
	@gen_muzica = 'Techno',  -- invalid 
	@experienta = -3,        -- invalid 

	@plata = 1200;

SELECT * FROM Eveniment;
SELECT * FROM DJ;
SELECT * FROM Eveniment_DJ;
SELECT * FROM LoggingTable;



-- ex2
GO
CREATE OR ALTER PROCEDURE InsertData2
(
	@numeE VARCHAR(100),
	@data_e DATE,
	@descriere VARCHAR(200),

	@numeDJ VARCHAR(100),
	@prenumeDJ VARCHAR(100),
	@gen_muzica VARCHAR(100),
	@experienta INT,

	@plata INT
)
AS
BEGIN
	DECLARE @errorMessage VARCHAR(300)
	DECLARE @insertedIdEveniment INT
	DECLARE @insertedIdDJ INT

	-- =======================
	-- 1. INSERARE EVENIMENT
	-- =======================
	BEGIN TRAN
	BEGIN TRY
		SET @errorMessage = dbo.ValidateEveniment2(@numeE, @data_e, @descriere)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO Eveniment(nume, data_eveniment, descriere)
		VALUES (@numeE, @data_e, @descriere)

		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('INSERT', 'Eveniment', CURRENT_TIMESTAMP)

		COMMIT TRAN
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('TRANSACTION COMMITTED', 'Eveniment', CURRENT_TIMESTAMP)

	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('TRANSACTION ROLLBACKED', 'Eveniment', CURRENT_TIMESTAMP)
	END CATCH

	-- =======================
	-- 2. INSERARE DJ
	-- =======================
	BEGIN TRAN
	BEGIN TRY
		SET @errorMessage = dbo.ValidateDJ2(@numeDJ, @prenumeDJ, @gen_muzica, @experienta)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO DJ(nume, prenume, gen_muzica, experienta)
		VALUES (@numeDJ, @prenumeDJ, @gen_muzica, @experienta)

		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('INSERT', 'DJ', CURRENT_TIMESTAMP)

		COMMIT TRAN
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('TRANSACTION COMMITTED', 'DJ', CURRENT_TIMESTAMP)

	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('TRANSACTION ROLLBACKED', 'DJ', CURRENT_TIMESTAMP)
	END CATCH

	IF @errorMessage != ''
	BEGIN
		RETURN
	END

	-- ==============================
	-- 3. INSERARE IN Eveniment_DJ
	-- ==============================
	-- Doar dacă am ambele ID-uri
	SELECT @insertedIdEveniment = MAX(id_eveniment) FROM Eveniment
	SELECT @insertedIdDJ = MAX(id_dj) FROM DJ

	BEGIN TRAN
	BEGIN TRY
		SET @errorMessage = dbo.ValidateEvenimentDJ2(@insertedIdEveniment, @insertedIdDJ, @plata)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO Eveniment_DJ(id_eveniment, id_dj, plata)
		VALUES (@insertedIdEveniment, @insertedIdDJ, @plata)

		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('INSERT', 'Eveniment_DJ', CURRENT_TIMESTAMP)

		COMMIT TRAN
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('TRANSACTION COMMITTED', 'Eveniment_DJ', CURRENT_TIMESTAMP)

	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		INSERT INTO LoggingTable(operationType, tableName, executionTime)
		VALUES ('TRANSACTION ROLLBACKED', 'Eveniment_DJ', CURRENT_TIMESTAMP)
	END CATCH
END
GO

-- executie cu succes
EXEC InsertData2 
	@numeE = 'Electric Castle',
	@data_e = '2025-08-01',
	@descriere = 'Festival de muzică în Bonțida',

	@numeDJ = 'David',
	@prenumeDJ = 'Guetta',
	@gen_muzica = 'Pop',
	@experienta = 20,

	@plata = 15000;

SELECT * FROM Eveniment;
SELECT * FROM DJ;
SELECT * FROM Eveniment_DJ;
SELECT * FROM LoggingTable;

--executie cu eroare
EXEC InsertData2 
	@numeE = 'Untold',
	@data_e = '2025-07-15',
	@descriere = 'Festival de muzică în Cluj',

	@numeDJ = 'Test',
	@prenumeDJ = 'Invalid',
	@gen_muzica = 'Techno',   -- INVALID
	@experienta = -1,         -- INVALID

	@plata = 8000;

SELECT * FROM Eveniment;
SELECT * FROM DJ;
SELECT * FROM Eveniment_DJ;
SELECT * FROM LoggingTable;
