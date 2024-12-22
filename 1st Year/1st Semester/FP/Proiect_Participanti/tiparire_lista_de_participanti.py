def afiseaza_participanti(participanti):
    for index, participant in enumerate(participanti):
        print(f"Participantul {index + 1} are următoarele scoruri:")
        for proba in range(1, 11):
            print(f"Scorul la proba {proba}: {participant[f"proba{proba}"]}")

def concurenti_cu_nota_mica(participanti, proba, nota_maxima):
    concurenti_nota_mica = []
    if 1 <= proba <= 10:
        for participant in participanti:
            if participant[f"proba{proba}"] < nota_maxima:
                concurenti_nota_mica.append(participant["id_participant"])
    return concurenti_nota_mica

def tipareste_participanti_ordonati_proba(participanti, proba):
    if 1 <= proba <= 10:
        participanti_ordonati = sorted(participanti, key=lambda x: x[f"proba{proba}"])
        print(f"Participanți ordonați după scor la proba {proba}:")
        for participant in participanti_ordonati:
            print(
                f"Participant {participant['id_participant']+1}: Scor la proba {proba} = {participant[f'proba{proba}']}")


def tipareste_participanti_scor_mai_mare_proba(participanti, proba, scor_dat):
    concurenti_nota_mare = []
    if 1 <= proba <= 10:
        participanti_ordonati = sorted(participanti, key=lambda x: x[f"proba{proba}"])
        for participant in participanti_ordonati:
            if participant[f"proba{proba}"] > scor_dat:
                concurenti_nota_mare.append(participant["id_participant"] + 1)
    print(f"Concurentii cu nota mai mare decat {scor_dat} la proba: {proba} sunt: {concurenti_nota_mare}")

