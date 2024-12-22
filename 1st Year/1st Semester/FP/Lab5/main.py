participant = []
index = int(0)
undo_stack=[]
def adauga_participant(participanti):
    global index
    scoruri = []
    for i in range(10):
        nota = int(input(f"Introduceți nota pentru proba {i + 1} (de la 1 la 10): "))
        if 1 <= nota <= 10:
            scoruri.append(nota)
        else:
            print("Scor invalid")
            return
    dictionar = {"id_participant": index, "proba1": scoruri[0], "proba2": scoruri[1], "proba3": scoruri[2],
                 "proba4": scoruri[3], "proba5": scoruri[4], "proba6": scoruri[5], "proba7": scoruri[6],
                 "proba8": scoruri[7], "proba9": scoruri[8], "proba10": scoruri[9]
                 }
    participanti.append(dictionar)
    undo_stack.append(participant.copy())
    print(undo_stack)
    index = index+1

def undo():
    global participant, undo_stack
    if undo_stack:
        print(undo_stack)
        participant = undo_stack.pop()
        print(participant)
def tipareste_participanti(participanti):
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

def filtrare_participanti_scor_multiplu_nr(participanti, numar_dat):
    for i in range(len(participanti)):
        for j in range(10):
            if participanti[i][f"proba{j+1}"] is not None:
                if participanti[i][f"proba{j+1}"] % numar_dat == 0:
                    participanti[i][f"proba{j+1}"] = None
    undo_stack.append(participant[:])
    print(undo_stack)


def filtrare_participanti_scor_mic_decat_scor_dat(participanti, numar1_dat):
    for i in range(len(participanti)):
        for j in range(10):
            if participanti[i][f"proba{j+1}"] is not None:
                if participanti[i][f"proba{j+1}"] < numar1_dat:
                    participanti[i][f"proba{j+1}"] = None
    return participanti

def verifica_participant(participanti, numar_participant):
    return 1 <= numar_participant <= len(participanti)

def sterge_scor(participanti, numar_participant):
    del participanti[numar_participant - 1]

def sterge_interval_scor_participanti(participanti, inceput, sfarsit):
    if 1 <= inceput <= sfarsit <= len(participanti):
        del participanti[inceput - 1:sfarsit]

def inlocuieste_scor(participanti, participant, scoruri_noi):
    if 1 <= participant <= len(participanti) and len(scoruri_noi) == 10:
        participanti[participant-1]["proba1"] = scoruri_noi[0]
        participanti[participant-1]["proba2"] = scoruri_noi[1]
        participanti[participant-1]["proba3"] = scoruri_noi[2]
        participanti[participant-1]["proba4"] = scoruri_noi[3]
        participanti[participant-1]["proba5"] = scoruri_noi[4]
        participanti[participant-1]["proba6"] = scoruri_noi[5]
        participanti[participant-1]["proba7"] = scoruri_noi[6]
        participanti[participant-1]["proba8"] = scoruri_noi[7]
        participanti[participant-1]["proba9"] = scoruri_noi[8]
        participanti[participant-1]["proba10"] = scoruri_noi[9]
    else:
        print("Participantul sau scorurile noi sunt invalide. Asigurați-vă că numărul participantului este valid și "
              "că ați introdus 10 scoruri noi.")

def inserare_scor(participanti, nr_participant):
    ok = int(0)
    for i in range(10):
        if participanti[nr_participant - 1][i] is None:
            ok = 1
    if ok:
        scor_nou = []
        for i in range(10):
            if participanti[nr_participant - 1][i] is None:
                scor_proba = int(input(f"Introduceti scorul pentru proba {i+1}: "))
                if 0 < scor_proba < 11:
                    scor_nou.append(scor_proba)
                else:
                    print("Scor introdus invalid")
                    break
            else:
                scor_nou.append(participanti[nr_participant-1][i])
        participanti[nr_participant-1] = scor_nou
    else:
        print("Participantul are deja scor la toate probele")


def media_scoruri_interval_dat(participanti, nr_inceput, nr_sfarsit):
    suma = int(0)
    for i in range(10):
        for j in range(nr_inceput, nr_sfarsit + 1):
            suma += participanti[j - 1][f"proba{i+1}"]
    media = float(suma/(10*(nr_sfarsit-nr_inceput+1)))
    media = round(media, 2)
    return media

def scorul_minim_pentru_interval(participanti, nr_inceput, nr_sfarsit):
    minim = int(11)
    for i in range(10):
        for j in range(nr_inceput, nr_sfarsit+1):
            if participanti[j-1][f"proba{i+1}"] < minim:
                minim = participanti[j - 1][f"proba{i+1}"]
    return minim

def scor_multiplu_zece_interval_dat(participanti, nr_inceput, nr_sfarsit):
    concurenti_scor_zece = []
    for j in range(nr_inceput, nr_sfarsit+1):
        suma = int(0)
        for i in range(10):
            suma = suma+participanti[j-1][f"proba{i+1}"]
        if 0 == suma%10:
            concurenti_scor_zece.append(j)
    return concurenti_scor_zece

def test_sterge_sor():
    participant = [
        {"id_participant": 0, "proba1": 2, "proba2": 1, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 6,
         "proba8": 7, "proba9": 8, "proba10": 9},

        {"id_participant": 1, "proba1": 10, "proba2": 9, "proba3": 8,
         "proba4": 7, "proba5": 6, "proba6": 5, "proba7": 4,
         "proba8": 2, "proba9": 3, "proba10": 1},

        {"id_participant": 2, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4},

        {"id_participant": 3, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4}
    ]
    sterge_scor(participant, 4)
    assert len(participant) == 3
def teste_sterge_interval_scor():
    participant = [
        {"id_participant": 0, "proba1": 2, "proba2": 1, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 6,
         "proba8": 7, "proba9": 8, "proba10": 9},

        {"id_participant": 1, "proba1": 10, "proba2": 9, "proba3": 8,
         "proba4": 7, "proba5": 6, "proba6": 5, "proba7": 4,
         "proba8": 2, "proba9": 3, "proba10": 1},

        {"id_participant": 2, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4},

        {"id_participant": 3, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4}
    ]

    sterge_interval_scor_participanti(participant, 1, 3)
    assert len(participant) == 1
def teste_inlocuire_scor():
    participant = [
        {"id_participant": 0, "proba1": 2, "proba2": 1, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 6,
         "proba8": 7, "proba9": 8, "proba10": 9},

        {"id_participant": 1, "proba1": 10, "proba2": 9, "proba3": 8,
         "proba4": 7, "proba5": 6, "proba6": 5, "proba7": 4,
         "proba8": 2, "proba9": 3, "proba10": 1},

        {"id_participant": 2, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4},

        {"id_participant": 3, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4}
    ]
    inlocuieste_scor(participant, 3, [10, 10, 10, 10, 10, 10, 10, 10, 10, 10])
    assert participant[2]["proba1"] == 10
    assert participant[2]["proba2"] == 10
    assert participant[2]["proba3"] == 10
    assert participant[2]["proba4"] == 10
    assert participant[2]["proba5"] == 10
    assert participant[2]["proba6"] == 10
    assert participant[2]["proba7"] == 10
    assert participant[2]["proba8"] == 10
    assert participant[2]["proba9"] == 10
    assert participant[2]["proba10"] == 10

    inlocuieste_scor(participant, 2, [10, 10, 10, 10, 10, 10, 10, 10, 10, 10])
    assert participant[1]["proba1"] == 10
    assert participant[1]["proba2"] == 10
    assert participant[1]["proba3"] == 10
    assert participant[1]["proba4"] == 10
    assert participant[1]["proba5"] == 10
    assert participant[1]["proba6"] == 10
    assert participant[1]["proba7"] == 10
    assert participant[1]["proba8"] == 10
    assert participant[1]["proba9"] == 10
    assert participant[1]["proba10"] == 10
def teste():
    participant = [
        {"id_participant": 0, "proba1": 2, "proba2": 1, "proba3": 2,
                 "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 6,
                 "proba8": 7, "proba9": 8, "proba10": 9},

        {"id_participant": 1, "proba1": 10, "proba2": 9, "proba3": 8,
         "proba4": 7, "proba5": 6, "proba6": 5, "proba7": 4,
         "proba8": 2, "proba9": 3, "proba10": 1},

        {"id_participant": 2, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4},

        {"id_participant": 3, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4},

        {"id_participant": 4, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4},

        {"id_participant": 5, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4},

        {"id_participant": 6, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4}
    ]

    assert len(participant) == 7

    assert concurenti_cu_nota_mica(participant, 2, 5) == [0, 2, 3, 4, 5, 6]

    epsilon = 0.00000000001
    assert (abs(media_scoruri_interval_dat(participant, 1, 3) - 4.77) < epsilon)

    assert scorul_minim_pentru_interval(participant, 1, 3) == 1

    assert scor_multiplu_zece_interval_dat(participant, 1, 3) == []

"""def teste_filtrare():
    participant = [
        {"id_participant": 0, "proba1": 2, "proba2": 1, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 6,
         "proba8": 7, "proba9": 8, "proba10": 9},

        {"id_participant": 1, "proba1": 10, "proba2": 9, "proba3": 8,
         "proba4": 7, "proba5": 6, "proba6": 5, "proba7": 4,
         "proba8": 2, "proba9": 3, "proba10": 1},

        {"id_participant": 2, "proba1": 3, "proba2": 2, "proba3": 2,
         "proba4": 3, "proba5": 4, "proba6": 5, "proba7": 3,
         "proba8": 7, "proba9": 8, "proba10": 4}
    ]
    assert (filtrare_participanti_scor_multiplu_nr(participant, 3)) == [
        {'id_participant': 0, 'proba1': 2, 'proba2': 1, 'proba3': 2,
         'proba4': None, 'proba5': 4, 'proba6': 5, 'proba7': None,
         'proba8': 7, 'proba9': 8, 'proba10': None},

        {"id_participant": 1, "proba1": 10, "proba2": None, "proba3": 8,
         "proba4": 7, "proba5": None, "proba6": 5, "proba7": 4,
         "proba8": 2, "proba9": None, "proba10": 1},

        {"id_participant": 2, "proba1": None, "proba2": 2, "proba3": 2,
         "proba4": None, "proba5": 4, "proba6": 5, "proba7": None,
         "proba8": 7, "proba9": 8, "proba10": 4}
        ]

    assert (filtrare_participanti_scor_mic_decat_scor_dat(participant, 2)) == [
        {'id_participant': 0, 'proba1': 2, 'proba2': None, 'proba3': 2,
         'proba4': None, 'proba5': 4, 'proba6': 5, 'proba7': None,
         'proba8': 7, 'proba9': 8, 'proba10': None},

        {"id_participant": 1, "proba1": 10, "proba2": None, "proba3": 8,
         "proba4": 7, "proba5": None, "proba6": 5, "proba7": 4,
         "proba8": 2, "proba9": None, "proba10": None},

        {"id_participant": 2, "proba1": None, "proba2": 2, "proba3": 2,
         "proba4": None, "proba5": 4, "proba6": 5, "proba7": None,
         "proba8": 7, "proba9": 8, "proba10": 4}
    ]"""
def teste_toate():
    teste()
    #teste_filtrare()
    teste_inlocuire_scor()
    test_sterge_sor()
    teste_sterge_interval_scor()
def main():
    global participant
    global undo_stack
    while True:
        print("Meniu:")
        print("1. Adaugă un participant")
        print("2. Modificare scor")
        print("3. Tipărește lista de participanți")
        print("4. Operatii pe un subset de participanti")
        print("5. Filtrare")
        print("6. Undo")
        print("7. Ieșire")

        optiune = input("Alege o opțiune: ")

        if optiune == "1":
            print("1. Adauga participant")
            print("2. Inserare scor pentru un participant")
            optiune_1 = input("Alegeti optiunea:")
            if optiune_1 == "1":
                adauga_participant(participant)
            elif optiune_1 == "2":
                nr_participant = int(input("Introduceti numarul participantului: "))
                if verifica_participant(participant, nr_participant):
                    inserare_scor(participant, nr_participant)
                else:
                    print("Numar participant invalid")
            else:
                print("Optiune invalida")
        elif optiune == "2":
            print("1. Sterge scorul pentru un participant")
            print("2. Sterge scorul pentru un interval de participanti")
            print("3. Inlocuieste scorul de la un participant")
            optiune1 = input("Alegeti optiunea: ")
            if optiune1 == "1":
                nr_part = int(input("Introduceti nr. participantului: "))
                if verifica_participant(participant, nr_part):
                    sterge_scor(participant, nr_part)
                else:
                    print("Numar participant invalid")
            elif optiune1 == "2":
                nr_inceput = int(input(" Introduceti inceputul intervalului: "))
                nr_sfarsit = int(input(" Introduceti sfarsitul intervalului: "))
                if verifica_participant(participant, nr_inceput) and verifica_participant(participant, nr_sfarsit):
                    sterge_interval_scor_participanti(participant, nr_inceput, nr_sfarsit)
                else:
                    print("Interval invalid")

            elif optiune1 == "3":
                participant1 = int(input("Introduceți numărul participantului pentru înlocuire: "))
                if verifica_participant(participant, participant1):
                    scoruri_noi = [int(input(f"Introduceți scorul pentru proba {i + 1}: ")) for i in range(10)]
                    ok = int(1)
                    for i in range(len(scoruri_noi)):
                        if scoruri_noi[i] < 1 or scoruri_noi[i] > 10:
                            ok = int(0)
                    if ok:
                        inlocuieste_scor(participant, participant1, scoruri_noi)
                    else:
                        print("Scoruri invalide")
                else:
                    print("Numar participant invalid")
            else:
                print("Opțiune invalidă. Încercați din nou.")

        elif optiune == "3":
            print("1.Lista de participanți:")
            print("2.Concurenți cu notă mai mică la o probă decât un număr dat")
            print("3.Tipărește participanții ordonati după scor la o anumita proba")
            print("4.Participanții cu scor mai mare decât un scor dat, ordonati dupa scor")
            optiune2 = input("Alegei o optiune: ")

            if optiune2 == "1":
                tipareste_participanti(participant)
            elif optiune2 == "2":
                proba = int(input("Introduceți proba pentru verificare (1-10): "))
                nota_maxima = int(input("Introduceți nota maximă: "))
                if 0 <= proba <= 10 and 0 < nota_maxima < 11:
                    concurenti = concurenti_cu_nota_mica(participant, proba, nota_maxima)
                    print(f"Concurenții cu notă mai mică decât {nota_maxima} la proba {proba}: {concurenti}")
                else:
                    print("Valori invalide")
            elif optiune2 == "3":
                proba = int(input("Introduceți proba pentru ordonare (1-10): "))
                if 1 <= proba <= 10:
                    tipareste_participanti_ordonati_proba(participant, proba)
                else:
                    print("Proba invalida")
            elif optiune2 == "4":
                proba = int(input("Introduceți proba pentru verificare (1-10): "))
                scor_dat = int(input("Introduceți scorul minim: "))
                if 0 <= proba <= 10 and 0 < scor_dat < 11:
                    tipareste_participanti_scor_mai_mare_proba(participant, proba, scor_dat)
                else:
                    print("Valori invalide")
            else:
                print("Opțiune invalidă. Încercați din nou.")

        elif optiune == "4":
            print("1.Calculează media scorurilor pentru un interval dat")
            print("2.Calculează scorul minim pentru un interval de participanți dat")
            print("3.Tipărește participanții dintr-un interval dat care au scorul multiplu de 10")
            optiune4 = int(input("Alegeti o optiune: "))
            if optiune4 == 1:
                interval1 = int(input("Introduceti primul capat al intervalului: "))
                interval2 = int(input("Introduceti ultimul capat al intervalului: "))
                if verifica_participant(participant, interval1) and verifica_participant(participant, interval2):
                    print("Media este: ", media_scoruri_interval_dat(participant, interval1, interval2))

            elif optiune4 == 2:
                interval1 = int(input("Introduceti primul capat al intervalului: "))
                interval2 = int(input("Introduceti ultimul capat al intervalului: "))
                if verifica_participant(participant, interval1) and verifica_participant(participant, interval2):
                    print("Scorul minim este: ", scorul_minim_pentru_interval(participant, interval1, interval2))

            elif optiune4 == 3:
                interval11 = int(input("Introduceti primul capat al intervalului: "))
                interval22 = int(input("Introduceti ultimul capat al intervalului: "))
                if verifica_participant(participant, interval11) and verifica_participant(participant, interval22):
                    print("Concurentii cu scorul multiplu de zece sunt: ",
                          scor_multiplu_zece_interval_dat(participant, interval11, interval22))

            else:
                print("Optiune invalida")

        elif optiune == "5":
            print("1.Filtrare participanți care au scorul multiplu unui număr dat")
            print("2.Filtrare participanți care au scorul mai mic decat un scor dat")
            optiune3 = input("Alegeti o optiune: ")
            if optiune3 == "1":
                numar_dat = int(input("Introduceti numarul: "))
                filtrare_participanti_scor_multiplu_nr(participant, numar_dat)

            elif optiune3 == "2":
                numar1_dat = int(input("Introduceti numarul: "))
                participant = filtrare_participanti_scor_mic_decat_scor_dat(participant, numar1_dat)

            else:
                print("Opțiune invalidă. Încercați din nou.")
        elif optiune == "6":
            undo()
        elif optiune == "7":
            break
        else:
            print("Opțiune invalid. Încercați din nou.")

#from teste import main_teste
#main_teste()
#teste_toate()
main()
