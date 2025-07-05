
-- aceeasi interogare executata de doua ori in aceeasi
-- tranzactie a returnat doua valori diferite pentru aceeasi inregistrare
CREATE OR ALTER PROCEDURE UnrepeatableReadsT1 AS
BEGIN
	-- SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;  --  pentru evitare
	BEGIN TRAN;
    BEGIN TRY
		SELECT * FROM DJ;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('select', 'DJ', CURRENT_TIMESTAMP);        
		WAITFOR DELAY '00:00:06';
		SELECT * FROM DJ;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('select', 'DJ', CURRENT_TIMESTAMP);        
        COMMIT TRAN;
        PRINT 'Transaction committed' ;
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;
        PRINT 'Transaction rolled back' ;
    END CATCH;
END;

EXEC UnrepeatableReadsT1;

SELECT * FROM DJ;