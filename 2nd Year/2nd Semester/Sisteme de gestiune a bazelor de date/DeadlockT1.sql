
-- Deadlock Transaction 1
CREATE OR ALTER PROCEDURE DeadlockT1 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
    BEGIN TRAN;
    BEGIN TRY

		UPDATE Eveniment SET descriere = 'deadlock t6' WHERE id_eveniment = 1;
        INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('UPDATE', 'Eveniment', CURRENT_TIMESTAMP);

        WAITFOR DELAY '00:00:05';

		UPDATE DJ SET nume = 'deadlock t6' WHERE id_dj = 1;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('UPDATE', 'DJ', CURRENT_TIMESTAMP);        

		COMMIT TRAN;
        PRINT 'Transaction committed' ;
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;
        PRINT 'Transaction rolled back';
    END CATCH;
END;

EXEC DeadlockT1;

SELECT * FROM Eveniment;
SELECT * FROM DJ;