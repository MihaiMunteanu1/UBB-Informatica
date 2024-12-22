participant = []
undo_stack=[]
index=0
def verifica_participant(participanti, numar_participant):
    return 1 <= numar_participant <= len(participanti)
def copy_scor(participant):
    global undo_stack
    undo_stack.clear()
    for dic in participant[:]:
        undo_stack.append(dic.copy())
def undo(participant):
    if undo_stack:
        participant.clear()
        for dic in undo_stack:
            participant.append(dic)
        print("Undo realizat cu succes")
    else:
        print("Lista Undo este goala")

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
                from adaugare_scor import adauga_participant
                copy_scor(participant)
                adauga_participant(participant)
            elif optiune_1 == "2":
                nr_participant = int(input("Introduceti numarul participantului: "))
                if verifica_participant(participant, nr_participant):
                    from adaugare_scor import inserare_scor
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
                    from modificare_scor import sterge_scor
                    copy_scor(participant)
                    sterge_scor(participant, nr_part)
                else:
                    print("Numar participant invalid")
            elif optiune1 == "2":
                nr_inceput = int(input(" Introduceti inceputul intervalului: "))
                nr_sfarsit = int(input(" Introduceti sfarsitul intervalului: "))
                if verifica_participant(participant, nr_inceput) and verifica_participant(participant, nr_sfarsit):
                    from modificare_scor import sterge_interval_scor_participanti
                    copy_scor(participant)
                    sterge_interval_scor_participanti(participant, nr_inceput, nr_sfarsit)
                else:
                    print("Interval invalid")
            elif optiune1 == "3":
                participant_inlocuire = int(input("Introduceți numărul participantului pentru înlocuire: "))
                if verifica_participant(participant, participant_inlocuire):
                    scoruri_noi = [int(input(f"Introduceți scorul pentru proba {i + 1}: ")) for i in range(10)]
                    ok = int(1)
                    for i in range(len(scoruri_noi)):
                        if scoruri_noi[i] < 1 or scoruri_noi[i] > 10:
                            ok = int(0)
                    if ok:
                        from modificare_scor import inlocuieste_scor
                        copy_scor(participant)
                        inlocuieste_scor(participant, participant_inlocuire, scoruri_noi)
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
                from tiparire_lista_de_participanti import afiseaza_participanti
                afiseaza_participanti(participant)
            elif optiune2 == "2":
                proba = int(input("Introduceți proba pentru verificare (1-10): "))
                nota_maxima = int(input("Introduceți nota maximă: "))
                if 0 <= proba <= 10 and 0 < nota_maxima < 11:
                    from tiparire_lista_de_participanti import concurenti_cu_nota_mica
                    concurenti = concurenti_cu_nota_mica(participant, proba, nota_maxima)
                    print(f"Concurenții cu notă mai mică decât {nota_maxima} la proba {proba}: {concurenti}")
                else:
                    print("Valori invalide")
            elif optiune2 == "3":
                proba = int(input("Introduceți proba pentru ordonare (1-10): "))
                if 1 <= proba <= 10:
                    from tiparire_lista_de_participanti import tipareste_participanti_ordonati_proba
                    tipareste_participanti_ordonati_proba(participant, proba)
                else:
                    print("Proba invalida")
            elif optiune2 == "4":
                proba = int(input("Introduceți proba pentru verificare (1-10): "))
                scor_dat = int(input("Introduceți scorul minim: "))
                if 0 <= proba <= 10 and 0 < scor_dat < 11:
                    from tiparire_lista_de_participanti import tipareste_participanti_scor_mai_mare_proba
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
                    from opertatii_pe_un_subset_de_participanti import media_scoruri_interval_dat
                    print("Media este: ", media_scoruri_interval_dat(participant, interval1, interval2))

            elif optiune4 == 2:
                interval1 = int(input("Introduceti primul capat al intervalului: "))
                interval2 = int(input("Introduceti ultimul capat al intervalului: "))
                if verifica_participant(participant, interval1) and verifica_participant(participant, interval2):
                    from opertatii_pe_un_subset_de_participanti import scorul_minim_pentru_interval
                    print("Scorul minim este: ", scorul_minim_pentru_interval(participant, interval1, interval2))

            elif optiune4 == 3:
                interval11 = int(input("Introduceti primul capat al intervalului: "))
                interval22 = int(input("Introduceti ultimul capat al intervalului: "))
                if verifica_participant(participant, interval11) and verifica_participant(participant, interval22):
                    from opertatii_pe_un_subset_de_participanti import scor_multiplu_zece_interval_dat
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
                from filtrare import filtrare_participanti_scor_multiplu_nr
                copy_scor(participant.copy())
                participant=filtrare_participanti_scor_multiplu_nr(participant, numar_dat)
            elif optiune3 == "2":
                numar1_dat = int(input("Introduceti numarul: "))
                from filtrare import filtrare_participanti_scor_mic_decat_scor_dat
                copy_scor(participant)
                participant = filtrare_participanti_scor_mic_decat_scor_dat(participant, numar1_dat)
            else:
                print("Opțiune invalidă. Încercați din nou.")
        elif optiune == "6":
            undo(participant)

        elif optiune == "7":
            break
        else:
            print("Opțiune invalid. Încercați din nou.")

from teste import main_teste
main_teste()
#from teste_cu_assert import teste_toate
#teste_toate()
main()
