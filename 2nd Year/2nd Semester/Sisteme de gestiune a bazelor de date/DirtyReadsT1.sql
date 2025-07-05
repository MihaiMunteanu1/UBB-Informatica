-- Dirty Reads Transaction 1
-- cand un cititor citeste date necomise

CREATE OR ALTER PROCEDURE DirtyReadsT1 AS
BEGIN
	BEGIN TRAN;
	BEGIN TRY
        UPDATE DJ SET nume = 'ddd t9' WHERE id_dj = 1;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('UPDATE', 'DJ', CURRENT_TIMESTAMP);        
		WAITFOR DELAY '00:00:05';
		ROLLBACK TRAN;
		PRINT 'Transaction successfully rolled back' ;
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN;
		PRINT 'Transaction unsuccessfully rolled back' ;
	END CATCH;
END;

EXEC DirtyReadsT1;

SELECT * FROM LoggingTable;
SELECT * FROM DJ;