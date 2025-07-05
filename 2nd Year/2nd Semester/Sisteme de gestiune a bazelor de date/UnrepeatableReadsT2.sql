
CREATE OR ALTER PROCEDURE UnrepeatableReadsT2 AS
BEGIN
	BEGIN TRAN;
    BEGIN TRY
        WAITFOR DELAY '00:00:03';
        UPDATE DJ SET nume = 'AAAA' WHERE id_dj = 2;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('UPDATE', 'DJ', CURRENT_TIMESTAMP);        
        COMMIT TRAN;
        PRINT 'Transaction committed' ;
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;
        PRINT 'Transaction rolled back' ;
    END CATCH;
END;

EXEC UnrepeatableReadsT2;