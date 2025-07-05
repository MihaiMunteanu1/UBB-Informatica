-- Phantom Reads Transaction 2

CREATE OR ALTER PROCEDURE PhantomReadsT2 AS
BEGIN
    BEGIN TRAN;
    BEGIN TRY
        --WAITFOR DELAY '00:00:03';
        INSERT INTO DJ (nume, prenume,gen_muzica,experienta) VALUES ('eee', 'TTEST2', 'TTEST2',5);
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('INSERT', 'DJ', CURRENT_TIMESTAMP);        
        COMMIT TRAN;
        PRINT 'Transaction committed' ;
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;
        PRINT 'Transaction rolled back' ;
    END CATCH;
END;

EXEC PhantomReadsT2;