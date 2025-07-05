-- Deadlock Transaction 2
CREATE OR ALTER PROCEDURE DeadlockT2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
    BEGIN TRAN;
    BEGIN TRY
        UPDATE DJ SET nume = 'deadlock t7' WHERE id_dj = 1;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('UPDATE', 'DJ', CURRENT_TIMESTAMP);        

        WAITFOR DELAY '00:00:05';

		UPDATE Eveniment SET nume = 'deadlock t7' WHERE id_eveniment = 1;
        INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('UPDATE', 'Eveniment', CURRENT_TIMESTAMP);

        
		COMMIT TRAN;
        PRINT 'Transaction committed';
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;
        PRINT 'Transaction rolled back' ;
    END CATCH;
END;

EXEC DeadlockT2;

SELECT * FROM Eveniment;
SELECT * FROM DJ;

SELECT * FROM SistemDeLogare;

