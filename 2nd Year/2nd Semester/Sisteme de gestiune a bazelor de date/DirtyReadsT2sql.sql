-- Dirty Reads Transaction 2
CREATE OR ALTER PROCEDURE DirtyReadsT2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED; --COMMITED pentru evitare
	BEGIN TRAN;
	BEGIN TRY
		SELECT * FROM DJ;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('Select', 'DJ', CURRENT_TIMESTAMP);              
		COMMIT TRAN;
		PRINT 'Transaction committed';
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN;
		PRINT 'Transaction rolled back';
	END CATCH;
END;

EXEC DirtyReadsT2;

SELECT * FROM DJ;
SELECT * FROM SistemDeLogare;