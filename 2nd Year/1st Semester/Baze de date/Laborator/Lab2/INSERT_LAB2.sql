USE LLAB2;

INSERT INTO Eveniment (nume, data_eveniment, descriere) VALUES
('Balul Bobocilor', '2024-11-09', 'Balul Bobocilor UBB'),
('Concert INNA', '2024-10-26', 'Concert INNA'),
('Revelion','2024-10-31','Revelion 2025'),
('Discoteca aniilor 80', '2024-09-14', 'Discoteca aniilor 80');

INSERT INTO Eveniment (nume, data_eveniment, descriere) VALUES
('Untold', '2025-08-10', 'Festivalul Untold'),
('White Party', '2025-05-20', 'Petrecere cu tinuta alba'),
('Heart Society','2024-12-24','Petrecere Heart Society'),
('Romanian Songs Party', '2025-07-14', 'Petrecere cu muzica romaneasca');

DELETE FROM Eveniment
WHERE nume = 'Untold';

SELECT * FROM Eveniment

INSERT INTO Locatie (nume, adresa, capacitate) VALUES
('Sala Polivalenta', 'Aleea Stadionului nr.4', 15000),
('NOA', 'Strada Republicii nr.109', 1300),
('Form', 'Aleea Stadionului nr.2', 800);

INSERT INTO Locatie (nume, adresa, capacitate) VALUES
('Hillhouse', 'Feleacu nr.5', 300),
('Club Diamond', 'Strada Republicii nr.110', 500),
('Aroma', 'Calea Turzii nr. 329', 100);

SELECT * FROM Locatie

INSERT INTO Eveniment_Locatie (id_eveniment, id_locatie) VALUES
(1, 2), 
(2, 1), 
(3, 1); 

INSERT INTO Eveniment_Locatie (id_eveniment, id_locatie) VALUES
(4, 4),
(4, 6),
(6, 3),
(7, 3);

SELECT * FROM Eveniment_Locatie

INSERT INTO Barman (nume, prenume, ani_experienta) VALUES
('Andrei', 'Ion', 5),
('Vlad', 'Mihai', 3),
('Bogdan','Vasile',9);

SELECT * FROM Barman

INSERT INTO Ospatar (nume, prenume, ani_experienta) VALUES
('Radulescu', 'Marius', 4),
('Petrescu', 'Alina', 2),
('Camelia','Aura',7);

SELECT * FROM Ospatar

INSERT INTO Casier (nume, prenume) VALUES
('Dumitru', 'Andrei'),
('Vasilescu', 'Roxana'),
('Ana', 'Maria'),
('Eusebiu', 'Marcu');

SELECT * FROM Casier

INSERT INTO Garderobier (nume, prenume, nr_haine_in_garderoba) VALUES
('Georgescu', 'Ana', 350),
('Aurel','Vlaicu',null),
('Dumitrescu', 'Elena', 300);

INSERT INTO DJ (nume, prenume, gen_muzica, experienta) VALUES
('Shiver', 'Maximilian', 'Electronic', 5),
('Sauce', 'Andrei', 'Rap', 3),
('Under','Cristi','R&B',6);

SELECT * FROM DJ

INSERT INTO Paza (nume, prenume, nume_firma) VALUES
('David', 'Gabriel', 'BGS'),
('Seva','Adrian','SGPI'),
('Luca', 'Adrian', 'MAO');

INSERT INTO Eveniment_Barman (id_eveniment, id_barman) VALUES
(4, 4),
(6, 5),
(7, 6),
(8, 6);

INSERT INTO Eveniment_Barman (id_eveniment, id_barman) VALUES
(1, 4),
(2, 5),
(3, 6);

SELECT * FROM Eveniment_Barman

INSERT INTO Eveniment_Casier (id_eveniment, id_casier) VALUES
(1, 1), 
(2, 2),
(3, 3); 
INSERT INTO Eveniment_Casier (id_eveniment, id_casier) VALUES
(4, 1),
(6, 2),
(7, 3),
(8, 3);

SELECT * FROM Eveniment_Casier

INSERT INTO Eveniment_Garderobier (id_eveniment, id_garderobier) VALUES
(1, 1), 
(2, 2),
(3, 3); 
INSERT INTO Eveniment_Garderobier (id_eveniment, id_garderobier) VALUES
(4, 1),
(6, 2),
(7, 3),
(8, 3);

INSERT INTO Eveniment_DJ (id_eveniment, id_dj) VALUES
(1, 1),
(2, 2),
(3, 3); 
INSERT INTO Eveniment_DJ (id_eveniment, id_dj) VALUES
(4, 1),
(6, 2),
(7, 3),
(8, 3);

SELECT * FROM Eveniment_DJ
SELECT * FROM Eveniment

INSERT INTO Eveniment_Paza (id_eveniment, id_paza) VALUES
(1, 1), 
(2, 2),
(3, 3); 
INSERT INTO Eveniment_Paza (id_eveniment, id_paza) VALUES
(4, 1),
(6, 2),
(7, 3),
(8, 3);

INSERT INTO Eveniment_Ospatar (id_eveniment, id_ospatar) VALUES
(1, 1),
(2, 2), 
(3, 3);
INSERT INTO Eveniment_Ospatar (id_eveniment, id_ospatar) VALUES
(4, 1),
(6, 2),
(7, 3),
(8, 3);

INSERT INTO Mese (id_eveniment, locuri) VALUES
(1, 8), (1, 6),
(2, 10), (2, 8),
(3, 10), (3, 6);
INSERT INTO Mese (id_eveniment, locuri) VALUES
(4, 8), (4, 6),(4, 10), (4, 8),
(6, 10), (6, 10), (6, 8),(6, 10),
(7, 10), (7, 8),(7, 10),
(8, 10), (8, 8),(8, 10),(8, 6);

SELECT * FROM Mese

INSERT INTO Clienti (id_masa, nume, prenume) VALUES
(1, 'Marin', 'Andrei'),(1, 'Ciobanu', 'Razvan'),(1, 'Ionescu', 'Alin'),
(1, 'Georgescu', 'Maria'),

(2, 'Vasilescu', 'Radu'),(2, 'Popescu', 'Ioana'),(2, 'Radulescu', 'Sorin'),
(2, 'Grigore', 'Simona'),

(3, 'Popa', 'Cristina'),(3, 'Stan', 'Adriana'),(3, 'Diaconu', 'George'),
(3, 'Dumitru', 'Vlad'),

(4, 'Iordache', 'Elena'),(4, 'Lungu', 'Daniela'),(4, 'Preda', 'Cristian'),
(4, 'Neagu', 'Stefan'),

(5, 'Grigore', 'Mihai'),(5, 'Mitrea', 'Alexandra'),(5, 'Dragomir', 'Mihai'),
(5, 'Marin', 'Violeta'),

(6, 'Cristea', 'Florin'),(6, 'Voinea', 'Claudia'),(6, 'Dobre', 'Anca'),
(6, 'Pop', 'Andrei'),(6, 'Rusu', 'Iulia');

INSERT INTO Clienti (id_masa, nume, prenume) VALUES
(7, 'Tudor', 'Cosmin'),(7, 'Vasiliu', 'Ioana'),(7, 'Ilie', 'Marius'),
(7, 'Marcu', 'Florentina'),(7, 'Filip', 'Vlad'),(7, 'Gheorghiu', 'Mirela'),
(7, 'Manolache', 'Diana'),(7, 'Sandu', 'Gabriel'),

(8, 'Petrescu', 'Daria'),(8, 'Olteanu', 'Adrian'),(8, 'Chirila', 'Raluca'),
(8, 'Lazar', 'Teodora'),(8, 'Zamfir', 'Bogdan'),(8, 'Voicu', 'Catalin'),

(9, 'Iancu', 'Alexandru'),(9, 'Teodorescu', 'Bianca'),(9, 'Serban', 'Mihnea'),
(9, 'Badea', 'Raluca'),(9, 'Constantin', 'Emil'),(9, 'Baciu', 'Catalina'),
(9, 'Roman', 'Marius'),(9, 'Mihalache', 'Anca'),(9, 'Coman', 'Stefan'),
(9, 'Chivu', 'Diana'),

(10, 'Pavel', 'Florin'),(10, 'Enache', 'Silvia'),(10, 'Lazar', 'Nicoleta'),
(10, 'Bratu', 'Mihai'),(10, 'Dinca', 'Andreea'),(10, 'Neacsu', 'Robert'),
(10, 'Simion', 'Ana'),(10, 'Ion', 'Cristian'),

(11, 'Anghel', 'Teodor'),(11, 'Panait', 'Georgiana'),(11, 'Grosu', 'Claudiu'),
(11, 'Petrache', 'Andra'),(11, 'Moraru', 'Sorin'),(11, 'Voiculescu', 'Larisa'),

(12, 'Petrache', 'Andra'),(12, 'Moraru', 'Sorin'),(12, 'Voiculescu', 'Larisa'),

(13, 'Popa', 'Gabriela'),(13, 'Munteanu', 'Razvan'),

(14, 'Filip', 'Daniel'),(14, 'Craciun', 'Alina'),(14, 'Tanase', 'Marian'),

(15, 'Dima', 'Raluca'),(15, 'Georgescu', 'Tudor'),

(16, 'Stanescu', 'Miruna'),(16, 'Mihai', 'Alexandru'),

(17, 'Draghici', 'Andreea'),(17, 'Constantinescu', 'Ion'),

(18, 'Dinu', 'Roxana'),(18, 'Antonescu', 'Cosmin'),

(19, 'Neagu', 'Florina'),

(20, 'Iacob', 'Mihai'),(20, 'Nistor', 'Ioana'),

(21, 'Rosu', 'Daniel'),(21, 'Costache', 'Cristina');

SELECT * FROM Clienti
DELETE FROM Clienti

INSERT INTO Eveniment_Clienti (id_eveniment, id_client) VALUES
(1, 1),(1, 2), (2, 3), (2, 4), (3, 5), (3, 6), (1, 7),  (1, 8), (1, 9), 
(1, 10), (2, 11), (2, 12), (2, 13), (2, 14),(3, 15), (3, 16), (3, 17), 
(3, 18), (1, 19), (2, 20), (3, 21), (3, 22), (3, 23), (3, 24), (3, 25); 

INSERT INTO Eveniment_Clienti (id_eveniment, id_client) VALUES
(1, 26), (1, 27), (1, 28), (1, 29), (1, 30), (1, 31), (1, 32), (1, 33),

(2, 34), (2, 35), (2, 36), (2, 37), (2, 38), (2, 39), (2, 40), (2, 41),

(3, 42), (3, 43), (3, 44), (3, 45), (3, 46), (3, 47), (3, 48), (3, 49),

(4, 50), (4, 51), (4, 52), (4, 53), (4, 54), (4, 55), (4, 56), (4, 57),

(6, 58), (6, 59), (6, 60), (6, 61), (6, 62), (6, 63),

(7, 64), (7, 65), (7, 66), (7, 67), (7, 68), (7, 69), (7, 70), (7, 71),

(8, 72), (8, 73), (8, 74), (8, 75), (8, 76), (8, 77), (8, 78), (8, 79), (8, 80), (8, 81), (8, 82), (8, 83), (8, 84);

SELECT * FROM Eveniment_Clienti