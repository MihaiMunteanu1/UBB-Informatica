USE LLAB2;

--1. Toti clientii care participa la concertul INNA
SELECT C.nume, C.prenume
FROM Clienti C
INNER JOIN Eveniment_Clienti EC ON C.id_client = EC.id_client
INNER JOIN Eveniment E ON EC.id_eveniment = E.id_eveniment
WHERE E.nume = 'Concert INNA';

--2. Locatiile care au capacitate mai mare de 900 persoane
SELECT L.nume AS Nume, L.capacitate AS capacitate
FROM Locatie L
WHERE L.capacitate >= 900;

--3. Fiecare eveniment care are mai multi de 10 clienti, ordonati
--   crescator dupa numarul clientilor
SELECT E.nume AS eveniment, COUNT(EC.id_client) AS numar_clienti
FROM Eveniment E
INNER JOIN Eveniment_Clienti EC ON E.id_eveniment = EC.id_eveniment
GROUP BY E.nume
HAVING COUNT(EC.id_client) > 10
ORDER BY COUNT(EC.id_client);

-- 4. Locatiile care gazduiesc evenimente in mai multe date diferite
SELECT L.nume AS locatie, COUNT(DISTINCT E.data_eveniment) AS numar_evenimente
FROM Locatie L
INNER JOIN Eveniment_Locatie EL ON L.id_locatie = EL.id_locatie
INNER JOIN Eveniment E ON EL.id_eveniment = E.id_eveniment
GROUP BY L.nume
HAVING COUNT(DISTINCT E.data_eveniment) > 1;

-- 5. Lista evenimentelor distincte, data lor si numărul de locații 
-- unde va avea loc fiecare eveniment
SELECT DISTINCT E.nume AS eveniment, E.data_eveniment AS data_eveniment, 
				COUNT(DISTINCT EL.id_locatie) AS numar_locatii
FROM Eveniment E
INNER JOIN Eveniment_Locatie EL ON E.id_eveniment = EL.id_eveniment
GROUP BY E.nume, E.data_eveniment
ORDER BY E.data_eveniment;

-- 6. Ospatarii care lucreaza la evenimente in NOA
SELECT O.nume, O.prenume
FROM Ospatar O
INNER JOIN Eveniment_Ospatar EO ON O.id_ospatar = EO.id_ospatar
INNER JOIN Eveniment E ON EO.id_eveniment = E.id_eveniment
INNER JOIN Eveniment_Locatie EL ON E.id_eveniment = EL.id_eveniment
INNER JOIN Locatie L on EL.id_locatie = L.id_locatie
WHERE L.nume = 'NOA';

--7. Lista tuturor clientilor si la ce eveniment participa
SELECT C.nume AS nume_client, C.prenume AS prenume_client, E.nume AS eveniment
FROM Clienti C
INNER JOIN Eveniment_Clienti EC ON C.id_client = EC.id_client
INNER JOIN Eveniment E ON EC.id_eveniment = E.id_eveniment;

--8. Clientii care participa la evenimente in NOA
SELECT C.nume, C.prenume
FROM Clienti C
INNER JOIN Eveniment_Clienti EC ON C.id_client = EC.id_client
INNER JOIN Eveniment E ON EC.id_eveniment = E.id_eveniment
INNER JOIN Eveniment_Locatie EL ON E.id_eveniment = EL.id_eveniment
INNER JOIN Locatie L ON EL.id_locatie = L.id_locatie
WHERE L.nume = 'NOA';

--9. Clienții care participă la 'Concert INNA', dar nu la 'Balul Bobocilor'
SELECT C.id_client, C.nume, C.prenume
FROM Clienti C
INNER JOIN Eveniment_Clienti EC ON C.id_client = EC.id_client
INNER JOIN Eveniment E ON EC.id_eveniment = E.id_eveniment
WHERE E.nume = 'Concert INNA'
EXCEPT
SELECT C.id_client, C.nume, C.prenume
FROM Clienti C
INNER JOIN Eveniment_Clienti EC ON C.id_client = EC.id_client
INNER JOIN Eveniment E ON EC.id_eveniment = E.id_eveniment
WHERE E.nume = 'Balul Bobocilor';

--10. Numarul de locuri la mese la fiecare eveniment
SELECT E.nume AS eveniment, SUM(M.locuri) AS total_locuri
FROM Eveniment E
INNER JOIN Mese M ON E.id_eveniment = M.id_eveniment
GROUP BY E.nume	
ORDER BY SUM(M.locuri);