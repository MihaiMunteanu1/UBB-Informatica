CREATE DATABASE CompetitieHalloween;

USE CompetitieHalloween;

CREATE TABLE Participanti
(
	id_participant INT PRIMARY KEY IDENTITY NOT NULL,
	nume VARCHAR(100) NOT NULL,
	telefon VARCHAR(10) NOT NULL CHECK(TRY_CAST(telefon AS INT) IS NOT NULL),
	adresa VARCHAR(100) NOT NULL
);

CREATE TABLE Dovleci
(
	id_dovleac INT PRIMARY KEY IDENTITY NOT NULL,
	descriere VARCHAR(500) NOT NULL,
	data_decorarii DATE NOT NULL,
	[timp_decorare(ore)] TIME NOT NULL, 
	mentiune BIT NOT NULL
);


CREATE TABLE Evaluatori
(
	id_evaluator INT PRIMARY KEY IDENTITY NOT NULL,
	nume VARCHAR(100) NOT NULL,
	email VARCHAR(100) NOT NULL CHECK(email LIKE '%_@gmail.com'),
	data_nasterii DATE NOT NULL
);

CREATE TABLE DovleciParticipanti
(
	id_dovleac INT NOT NULL FOREIGN KEY REFERENCES Dovleci(id_dovleac) ON DELETE CASCADE ON UPDATE CASCADE,
	id_participant INT NOT NULL FOREIGN KEY REFERENCES Participanti(id_participant) ON DELETE CASCADE ON UPDATE CASCADE,
	descriere VARCHAR(200) NOT NULL,
	PRIMARY KEY(id_dovleac, id_participant)
);

CREATE TABLE DovleciEvaluatori
(
	id_dovleac INT NOT NULL FOREIGN KEY REFERENCES Dovleci(id_dovleac) ON DELETE CASCADE ON UPDATE CASCADE,
	id_evaluator INT NOT NULL FOREIGN KEY REFERENCES Evaluatori(id_evaluator) ON DELETE CASCADE ON UPDATE CASCADE,
	nota INT NOT NULL CHECK(nota <=10 AND nota >=1),
	PRIMARY KEY(id_dovleac, id_evaluator)
);

INSERT INTO Dovleci(descriere, data_decorarii, [timp_decorare(ore)], mentiune) VALUES
('dovleac sculptat cu cutitul', '2025-01-15', '05:30:00', 1),
('dovleac sculptat cu lingura', '2025-01-12', '04:45:00', 0),
('dovleac mediu', '2024-12-12', '06:00:00', 1),
('dovleac mare', '2024-12-12', '12:00:00', 0),
('dovleac mic', '2024-12-12', '04:00:00', 0);

INSERT INTO Participanti(nume, telefon, adresa) VALUES
('Vlad Mutu', '0770102742', 'Nufarului 48'),
('Mircea Marcu', '0722105124', 'Mestecenilor 6'),
('Gigel Popescu', '0772104182', 'Louis Pasteur 32'),
('Andrei Ionescu', '0742912812', 'Dimitrie Cantemir 54'),
('Marc Filipescu', '0770128938', 'Frunzisului 34'),
('Maria Pop', '0772317377', 'Observatorului 102'),
('Andreea Pop', '0747218366', 'Memorandumului 47');

INSERT INTO Evaluatori(nume, email, data_nasterii) VALUES
('Marcel Pop', 'marcelpop@gmail.com', '2004-12-12'),
('Marcu Sebastian', 'marcus@gmail.com', '2002-01-30'),
('Luca Popa', 'lucap@gmail.com', '2005-05-09');

INSERT INTO DovleciParticipanti(id_dovleac, id_participant, descriere) VALUES
(1, 2, 'test'),
(1, 3, 'test'),
(3, 1, 'test'),
(5, 1, 'test'),
(4, 4, 'test'),
(4, 5, 'test'),
(2, 5, 'test');

INSERT INTO DovleciEvaluatori(id_dovleac, id_evaluator, nota) VALUES
(1,1, 4),
(1,2, 3),
(1,3, 2),
(2,1, 6),
(2,3, 8),
(2,2, 7),
(3,1, 10),
(3,2, 10),
(3,3, 10),
(4,1, 1),
(4,2, 10),
(4,3, 5),
(5,1, 6),
(5,2, 8),
(5,3, 9);


GO
CREATE OR ALTER PROCEDURE AdaugaDescriere(@id_dovleac INT, @id_participant INT, @descriere VARCHAR(100))
AS
BEGIN
	IF EXISTS(SELECT * FROM DovleciParticipanti WHERE id_dovleac = @id_dovleac AND id_participant = @id_participant)
	BEGIN
		UPDATE DovleciParticipanti
		SET descriere = @descriere
		WHERE id_dovleac = @id_dovleac AND id_participant = @id_participant;
	END
	ELSE
	BEGIN
		INSERT INTO DovleciParticipanti(id_dovleac, id_participant, descriere) VALUES
		(@id_dovleac, @id_participant, @descriere);
	END
END
GO


GO
CREATE OR ALTER VIEW ViewNumeParticipant
AS
	SELECT TOP 1 COUNT(nume) AS Cati, nume FROM Participanti
	INNER JOIN DovleciParticipanti ON Participanti.id_participant = DovleciParticipanti.id_participant
	INNER JOIN Dovleci ON Dovleci.id_dovleac = DovleciParticipanti.id_dovleac
	WHERE Dovleci.mentiune = 1
	GROUP BY nume, Participanti.id_participant
	ORDER BY Cati DESC
GO

SELECT nume FROM ViewNumeParticipant
