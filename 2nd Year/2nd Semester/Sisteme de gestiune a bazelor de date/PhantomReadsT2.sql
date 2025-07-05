-- Phantom Reads Transaction 1

-- numarul de inregistrari din al doilea result set e mai mare decat
-- numarul de inregistrari din primul resul set


CREATE OR ALTER PROCEDURE PhantomReadsT1 AS
BEGIN
    --SET TRANSACTION ISOLATION LEVEL SERIALIZABLE; pentru evitare
    BEGIN TRANSACTION;
    BEGIN TRY
        SELECT * FROM DJ;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('Select', 'DJ', CURRENT_TIMESTAMP);        
        WAITFOR DELAY '00:00:06';
        SELECT * FROM DJ;
		INSERT INTO SistemDeLogare (operatie, tabel, timp) VALUES ('Select', 'DJ', CURRENT_TIMESTAMP);        
        COMMIT TRANSACTION;
        PRINT 'Transaction committed' ;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
        PRINT 'Transaction rolled back';
    END CATCH;
END;

EXEC PhantomReadsT1;

SELECT * FROM DJ;
select * from SistemDeLogare;