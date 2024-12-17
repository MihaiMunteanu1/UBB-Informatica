USE LLAB2;	

-- DJ <-> EVENIMENT-DJ <-> EVENIMENT <-> MESE

-- View ce contine o comanda select
-- Fiecare eveniment si in ce data se tine
GO 
CREATE VIEW View_Eveniment 
AS
	SELECT E.nume,E.data_eveniment FROM Eveniment E;
GO

-- View pe cel putin 2 tabele
-- Fiecare DJ la ce eveniment participa
CREATE VIEW View_DJ_Eveniment
AS
	SELECT DJ.nume as NumeDJ, DJ.prenume as PrenumeDJ ,DJ.gen_muzica as GenMuzica, E.nume
	FROM DJ
	INNER JOIN Eveniment_DJ EDJ on EDJ.id_dj=EDJ.id_eveniment
	INNER JOIN Eveniment E on EDJ.id_eveniment=E.id_eveniment
GO

-- View pe cel putin 2 tabele cu group by
-- Fiecare eveniment si numarul total de locuri la mese
CREATE VIEW View_Mese_Eveniment
AS
	SELECT E.nume AS eveniment, SUM(M.locuri) AS total_locuri
	FROM Eveniment E
	INNER JOIN Mese M ON E.id_eveniment = M.id_eveniment
	GROUP BY E.nume,E.id_eveniment;
GO

SELECT * FROM View_DJ_Eveniment;

SELECT * FROM View_Eveniment;

SELECT * FROM View_Mese_Eveniment;


INSERT INTO Tables (Name) VALUES
('DJ'),('Eveniment'),('Eveniment_DJ'),('Mese');

SELECT * FROM Tables


INSERT INTO Views(Name) VALUES
('View_Eveniment'),('View_DJ_Eveniment'),('View_Mese_Eveniment');

SELECT * FROM Views


INSERT INTO Tests (Name) VALUES
	('Test1');

SELECT * FROM Tests

INSERT INTO TestViews(TestID,ViewID) VALUES 
	(1,1),
	(1,2),
	(1,3);

SELECT * FROM TestViews


INSERT INTO TestTables(TestID,TableID,NoOfRows,Position) VALUES
	(1,3,10000,1),
	(1,4,10000,2),
	(1,1,10000,3),
	(1,2,10000,4);

SELECT * FROM TestTables


-- procedura de inserat evenimente
GO
CREATE OR ALTER PROCEDURE insertEvenimente @rows INT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @i INT = 0;
	DECLARE @id INT = (SELECT MAX(Eveniment.id_eveniment) FROM Eveniment)+1
	DECLARE @nume VARCHAR(100)
	DECLARE @data DATE

	WHILE @i < @rows
	BEGIN
		SET @nume = 'Eveniment ' + CONVERT(VARCHAR(100),@id)
		SET @data = '2025-01-01'
		INSERT INTO Eveniment(nume,data_eveniment) VALUES (@nume,@data);
		SET @id=@id+1
		SET @i=@i+1
	END
END


-- procedura de inserat dj
GO
CREATE OR ALTER PROCEDURE insertDJ @rows INT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @i INT = 0;
	DECLARE @id INT = (SELECT MAX(DJ.id_dj) FROM DJ)+1
	DECLARE @nume VARCHAR(100)
	DECLARE @prenume VARCHAR(100)
	DECLARE @experienta INT

	WHILE @i < @rows
	BEGIN
		SET @nume = 'DJ ' + CONVERT(VARCHAR(100),@id)
		SET @prenume = 'DJ ' + CONVERT(VARCHAR(100),@id)
		SET @experienta = @id
		INSERT INTO DJ(nume,prenume,experienta) VALUES (@nume,@prenume,@experienta);
		SET @id=@id+1
		SET @i=@i+1
	END
END


-- procedura de inserat mese
GO
CREATE OR ALTER PROCEDURE insertMese @rows INT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @i INT = 0;
	DECLARE @id INT = (SELECT MAX(Mese.id_masa) FROM Mese)+1
	DECLARE @id_e INT = (SELECT MAX(Eveniment.id_eveniment) FROM Eveniment)
	DECLARE @locuri INT

	WHILE @i < @rows
	BEGIN
		SET @locuri = @id
		INSERT INTO Mese(id_eveniment,locuri) VALUES (@id_e,(@locuri % 10) + 1 );
		SET @id=@id+1
		SET @id_e=@id_e-1
		SET @i=@i+1
	END
END


-- procedura de inserat pentru EvenimentDJ
GO
CREATE OR ALTER PROCEDURE inserareEvenimentDJ @rows INT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @i INT = 0;
	DECLARE @id_e INT = (SELECT MIN(Eveniment.id_eveniment) FROM Eveniment
						WHERE Eveniment.nume LIKE 'Eveniment%');
	DECLARE @id_dj INT = (SELECT MIN(DJ.id_dj) FROM DJ
						WHERE DJ.nume LIKE 'DJ%');

	WHILE @i < @rows 
	BEGIN
		INSERT INTO Eveniment_DJ(id_eveniment,id_dj) VALUES (@id_e, @id_dj);
		SET @id_e = @id_e + 1;
		SET @id_dj = @id_dj + 1;
		SET @i = @i + 1;
	END
END


-- procedura de stergere evenimente
GO
CREATE OR ALTER PROCEDURE stergeEvenimente
AS
BEGIN
	SET NOCOUNT ON;

	DELETE FROM Eveniment
	WHERE Eveniment.nume LIKE 'Eveniment%'
END

-- procedura de stergere dj
GO
CREATE OR ALTER PROCEDURE stergeDJ
AS
BEGIN
	SET NOCOUNT ON;

	DELETE FROM DJ
	WHERE DJ.nume LIKE 'DJ%'
END

-- procedura de stergere mese
GO
CREATE OR ALTER PROCEDURE stergeMese
AS
BEGIN
	SET NOCOUNT ON;

	DELETE FROM Mese
	WHERE id_masa > 21
END

-- procedura de stergere evenimentDJ
GO
CREATE OR ALTER PROCEDURE stergeEvenimentDJ
AS
BEGIN
	SET NOCOUNT ON;

    DECLARE @id INT = (SELECT MIN(Eveniment.id_eveniment) FROM Eveniment
						WHERE Eveniment.nume LIKE 'Eveniment%')

	DELETE FROM Eveniment_DJ
	WHERE Eveniment_DJ.id_eveniment >= @id
END

--------------------------------------------------------------------------
-- procedura generala pentru insert

GO
CREATE OR ALTER PROCEDURE GeneralInsert @TestID INT
AS
BEGIN

    DECLARE @TableID INT;
    DECLARE @TableName NVARCHAR(100);
    DECLARE @NoOfRows INT;
    DECLARE @Position INT;

    DECLARE cursorTables CURSOR FOR
		SELECT TT.TableID, T.Name, TT.NoOfRows, TT.Position
		FROM TestTables TT
		INNER JOIN Tables T ON TT.TableID = T.TableID
		WHERE TT.TestID = @TestID
		ORDER BY TT.Position DESC;

    OPEN cursorTables;
    FETCH NEXT FROM cursorTables INTO @TableID, @TableName, @NoOfRows, @Position;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        IF @TableName = 'Eveniment'
        BEGIN
            EXEC insertEvenimente @NoOfRows;
        END
        ELSE IF @TableName = 'DJ'
        BEGIN
            EXEC insertDJ @NoOfRows;
        END
        ELSE IF @TableName = 'Mese'
        BEGIN
            EXEC insertMese @NoOfRows;
        END
        ELSE IF @TableName = 'Eveniment_DJ'
        BEGIN
            EXEC inserareEvenimentDJ @NoOfRows;
        END

        FETCH NEXT FROM cursorTables INTO @TableID, @TableName, @NoOfRows, @Position;
    END

    CLOSE cursorTables;	
    DEALLOCATE cursorTables;
END;
GO


-- procedura generala pentru delete 

GO
CREATE OR ALTER PROCEDURE GeneralDelete @TestID INT
AS
BEGIN
    DECLARE @TableID INT;
    DECLARE @TableName NVARCHAR(100);
    DECLARE @Position INT;

    DECLARE cursorTables CURSOR FOR
		SELECT TT.TableID, T.Name, TT.Position
		FROM TestTables TT
		INNER JOIN Tables T ON TT.TableID = T.TableID
		WHERE TT.TestID = @TestID
		ORDER BY TT.Position ;

    OPEN cursorTables;
    FETCH NEXT FROM cursorTables INTO @TableID, @TableName, @Position;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        IF @TableName = 'Eveniment'
        BEGIN
            EXEC stergeEvenimente;
        END
        ELSE IF @TableName = 'DJ'
        BEGIN
            EXEC stergeDJ;
        END
        ELSE IF @TableName = 'Mese'
        BEGIN
            EXEC stergeMese;
        END
        ELSE IF @TableName = 'Eveniment_DJ'
        BEGIN
            EXEC stergeEvenimentDJ;
        END

        FETCH NEXT FROM cursorTables INTO @TableID, @TableName, @Position;
    END

    CLOSE cursorTables;
    DEALLOCATE cursorTables;
END;
GO



-- procedura generala pentru view

GO
CREATE OR ALTER PROCEDURE GeneralView @TestID INT
AS
BEGIN
    DECLARE @ViewID INT;
    DECLARE @ViewName NVARCHAR(100);
    DECLARE @Comanda NVARCHAR(MAX);

    DECLARE cursorViews CURSOR FOR
		SELECT V.ViewID, V.Name
		FROM TestViews TV
		INNER JOIN Views V ON TV.ViewID = V.ViewID
		WHERE TV.TestID = @TestID;

    OPEN cursorViews;
    FETCH NEXT FROM cursorViews INTO @ViewID, @ViewName;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @Comanda = N'SELECT * FROM [' + @ViewName +']';

        PRINT N'S-a executat view-ul: ' + @ViewName;
        EXECUTE (@Comanda);

        FETCH NEXT FROM cursorViews INTO @ViewID, @ViewName;
    END

    CLOSE cursorViews;
    DEALLOCATE cursorViews;
END;
GO

-- ------------------------------
-- Procedura principala

GO
CREATE OR ALTER PROCEDURE main @TestID INT
AS
BEGIN

	DBCC CHECKIDENT ('Eveniment', RESEED, 8);
	DBCC CHECKIDENT ('Mese', RESEED, 21);
	DBCC CHECKIDENT ('DJ', RESEED, 3);


    DECLARE @t1 DATETIME;
    DECLARE @t2 DATETIME;
    DECLARE @t3 DATETIME;

    DECLARE @TestName NVARCHAR(100) = 'Test1';
    DECLARE @TestRunID INT;	

    SET @t1 = GETDATE();

	EXEC GeneralDelete @TestID;
	
    EXEC GeneralInsert @TestID;

    SET @t2 = GETDATE();

    EXEC GeneralView @TestID;

    SET @t3 = GETDATE();

    INSERT INTO TestRuns (Description, StartAt, EndAt)
    VALUES (@TestName, @t1, @t3);

    -- luam id-ul rularii pt a-l insera in TestRunTables si TestRunViews
    SELECT TOP 1 @TestRunID = TestRunID
    FROM TestRuns
    ORDER BY TestRunID DESC;

    INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
		SELECT @TestRunID, TT.TableID, @t1, @t2
		FROM TestTables TT
		WHERE TT.TestID = @TestID;

    INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
		SELECT @TestRunID, TV.ViewID, @t2, @t3
		FROM TestViews TV
		WHERE TV.TestID = @TestID;

    PRINT 'Testul a durat: ' + CONVERT(VARCHAR(10), DATEDIFF(MILLISECOND, @t1, @t3)) + ' milisecunde.';
END;
GO

-------------------	
exec main 1

SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;

DELETE FROM TestRuns
DELETE FROM TestRunTables	
DELETE FROM TestRunViews

SELECT * FROM Eveniment
SELECT * FROM DJ
SELECT * FROM Mese
SELECT * FROM Eveniment_DJ

exec stergeEvenimente
exec stergeDJ
exec stergeMese
exec stergeEvenimentDJ

DBCC CHECKIDENT ('Eveniment', RESEED, 8);
DBCC CHECKIDENT ('Mese', RESEED, 21);
DBCC CHECKIDENT ('DJ', RESEED, 3);