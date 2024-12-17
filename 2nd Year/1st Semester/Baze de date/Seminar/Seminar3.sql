
CREATE DATABASE Seminar3;

USE Seminar3;

CREATE TABLE EchipamenteAgricole(
	cod_e INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(100),
	tip VARCHAR(100),
	model VARCHAR(100),
	data_ultimei_revizii DATE,
	pret INT,
	nr_cilindrii INT
);

GO
CREATE PROCEDURE AdaugaEchipamentAgricol
@nume VARCHAR(100), @tip VARCHAR(100), @model VARCHAR(100), @data_ultimei_revizii DATE,
@pret INT, @nr_cilindrii INT
AS
BEGIN
INSERT INTO EchipamenteAgricole(nume, tip, model,data_ultimei_revizii, pret, nr_cilindrii) VALUES
(@nume, @tip, @model, @data_ultimei_revizii, @pret, @nr_cilindrii);
END;

EXEC  AdaugaEchipamentAgricol 'tractor', 'nu stim', 'John Deere 6R', '2024-11-07',
125000, 6;

SELECT * FROM EchipamenteAgricole

DROP PROCEDURE AdaugaEchipamentAgricol