"""TESTE"""

def creeaza_participant(id_participant, proba1, proba2, proba3, proba4, proba5, proba6, proba7, proba8, proba9,
                                                                                                          proba10):
    return {
        "id_participant": id_participant,
        "proba1": proba1,
        "proba2": proba2,
        "proba3": proba3,
        "proba4": proba4,
        "proba5": proba5,
        "proba6": proba6,
        "proba7": proba7,
        "proba8": proba8,
        "proba9": proba9,
        "proba10": proba10
    }
def get_id_participant(lista_participanti):
    return lista_participanti["id_participant"]
def get_proba1(lista_participanti):
    return lista_participanti["proba1"]
def get_proba2(lista_participanti):
    return lista_participanti["proba2"]
def get_proba3(lista_participanti):
    return lista_participanti["proba3"]
def get_proba4(lista_participanti):
    return lista_participanti["proba4"]
def get_proba5(lista_participanti):
    return lista_participanti["proba5"]
def get_proba6(lista_participanti):
    return lista_participanti["proba6"]
def get_proba7(lista_participanti):
    return lista_participanti["proba7"]
def get_proba8(lista_participanti):
    return lista_participanti["proba8"]
def get_proba9(lista_participanti):
    return lista_participanti["proba9"]
def get_proba10(lista_participanti):
    return lista_participanti["proba10"]

def valideaza_participant(participant):
    eroare = ""
    id_participant = get_id_participant(participant)
    if not isinstance(id_participant, int) or id_participant < 0:
        eroare += "id invalid!\n"
    if not (1 <= get_proba1(participant) <= 10):
        eroare += "proba 1 invalida!\n"
    if not (1 <= get_proba2(participant) <= 10):
        eroare += "proba 2 invalida!\n"
    if not (1 <= get_proba3(participant) <= 10):
        eroare += "proba 3 invalida!\n"
    if not (1 <= get_proba4(participant) <= 10):
        eroare += "proba 4 invalida!\n"
    if not (1 <= get_proba5(participant) <= 10):
        eroare += "proba 5 invalida!\n"
    if not (1 <= get_proba6(participant) <= 10):
        eroare += "proba 6 invalida!\n"
    if not (1 <= get_proba7(participant) <= 10):
        eroare += "proba 7 invalida!\n"
    if not (1 <= get_proba8(participant) <= 10):
        eroare += "proba 8 invalida!\n"
    if not (1 <= get_proba9(participant) <= 10):
        eroare += "proba 9 invalida!\n"
    if not (1 <= get_proba10(participant) <= 10):
        eroare += "proba 10 invalida!\n"
    if len(eroare) > 0:
        raise Exception(eroare)
def adauga_participant_in_lista_de_participanti(lista_participanti, participant):
    for _participant in lista_participanti:
        if egal_participanti(_participant, participant):
            raise Exception("participant existent!\n")
    lista_participanti.append(participant)

def egal_participanti(participant1, participant2):
    return participant1["id_participant"] == participant2["id_participant"]

def test_adauga_participant_in_lista_de_participanti():
    lista_participanti = []
    id_participant_valid = 1
    proba1_valida = 1
    proba2_valida = 2
    proba3_valida = 3
    proba4_valida = 4
    proba5_valida = 5
    proba6_valida = 6
    proba7_valida = 7
    proba8_valida = 8
    proba9_valida = 9
    proba10_valida = 10
    participant_valid = creeaza_participant(id_participant_valid, proba1_valida, proba2_valida, proba3_valida,
                                            proba4_valida, proba5_valida, proba6_valida, proba7_valida, proba8_valida,
                                            proba9_valida, proba10_valida)
    assert (len(lista_participanti) == 0)
    adauga_participant_in_lista_de_participanti(lista_participanti, participant_valid)
    assert (len(lista_participanti) == 1)
    assert (egal_participanti(participant_valid, lista_participanti[0]))

    try:
        adauga_participant_in_lista_de_participanti(lista_participanti, participant_valid)
        assert False
    except Exception as ex:
        assert (str(ex) == "participant existent!\n")

def test_valideaza_participant():
    id_participant_valid = 1
    proba1_valida = 1
    proba2_valida = 2
    proba3_valida = 3
    proba4_valida = 4
    proba5_valida = 5
    proba6_valida = 6
    proba7_valida = 7
    proba8_valida = 8
    proba9_valida = 9
    proba10_valida = 10
    participant_valid = creeaza_participant(id_participant_valid, proba1_valida, proba2_valida, proba3_valida,
                                            proba4_valida, proba5_valida, proba6_valida, proba7_valida, proba8_valida,
                                            proba9_valida, proba10_valida)
    valideaza_participant(participant_valid)

    id_participant_invalid = -23
    proba1_invalida = -1
    proba2_invalida = 20
    proba3_invalida = 30
    proba4_invalida = 40
    proba5_invalida = 50
    proba6_invalida = 60
    proba7_invalida = 70
    proba8_invalida = 80
    proba9_invalida = 90
    proba10_invalida = 100
    participant_invalid = creeaza_participant(id_participant_invalid, proba1_invalida, proba2_invalida, proba3_invalida,
                                        proba4_invalida, proba5_invalida, proba6_invalida, proba7_invalida,
                                        proba8_invalida, proba9_invalida, proba10_invalida)
    try:
        valideaza_participant(participant_invalid)
        assert False
    except Exception as ex:
        assert "id invalid!" in str(ex)
        assert "proba 1 invalida" in str(ex)
        assert "proba 2 invalida" in str(ex)
        assert "proba 3 invalida" in str(ex)
        assert "proba 4 invalida" in str(ex)
        assert "proba 5 invalida" in str(ex)
        assert "proba 6 invalida" in str(ex)
        assert "proba 7 invalida" in str(ex)
        assert "proba 8 invalida" in str(ex)
        assert "proba 9 invalida" in str(ex)
        assert "proba 10 invalida" in str(ex)


def service_adauga_participant_in_lista(lista_participanti, id_participant, proba1, proba2, proba3, proba4, proba5,
                                                             proba6, proba7, proba8, proba9, proba10):
    particpant = creeaza_participant(id_participant, proba1, proba2, proba3, proba4, proba5,
                                                             proba6, proba7, proba8, proba9, proba10)
    valideaza_participant(particpant)
    adauga_participant_in_lista_de_participanti(lista_participanti, particpant)

def citeste_numar(prompt, f, msg):
    while True:
        try:
            return f(input(prompt))
        except ValueError:
            print(msg)

def ui_adauga_participant_in_lista_participanti(lista_participanti):
    id_participant = citeste_numar("introduceti un id intreg pozitiv: ", int, "valoare numerica invalida!")
    proba1 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 1: ", int, "valoare numerica invalida!")
    proba2 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 2: ", int, "valoare numerica invalida!")
    proba3 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 3: ", int, "valoare numerica invalida!")
    proba4 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 4: ", int, "valoare numerica invalida!")
    proba5 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 5: ", int, "valoare numerica invalida!")
    proba6 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 6: ", int, "valoare numerica invalida!")
    proba7 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 7: ", int, "valoare numerica invalida!")
    proba8 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 8: ", int, "valoare numerica invalida!")
    proba9 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 9: ", int, "valoare numerica invalida!")
    proba10 = citeste_numar("introduceti un nr. natural din intervalul [1, 10] pentru proba 10: ", int, "valoare numerica invalida!")
    service_adauga_participant_in_lista(lista_participanti, id_participant, proba1, proba2, proba3, proba4, proba5,
                                                             proba6, proba7, proba8, proba9, proba10)

"""def run():
    lista_participanti = []
    while True:
        cmd = input()
        if cmd == "adauga participant":
            try:
                ui_adauga_participant_in_lista_participanti(lista_participanti)
            except Exception as ex:
                print(ex)"""


def test_service_adauga_participant_in_lista_participanti():
    id_participant = 1
    proba1 = 1
    proba2 = 2
    proba3 = 3
    proba4 = 4
    proba5 = 5
    proba6 = 6
    proba7 = 7
    proba8 = 8
    proba9 = 9
    proba10 = 10
    lista_participanti = []
    service_adauga_participant_in_lista(lista_participanti, id_participant, proba1, proba2, proba3, proba4, proba5,
                                        proba6, proba7, proba8, proba9, proba10)
    assert (len(lista_participanti) == 1)
    participant = creeaza_participant(id_participant, proba1, proba2, proba3, proba4, proba5, proba6, proba7,
                                            proba8, proba9, proba10)
    assert (egal_participanti(participant, lista_participanti[0]))
    try:
        service_adauga_participant_in_lista(lista_participanti, id_participant, proba1, proba2, proba3, proba4, proba5,
                                        proba6, proba7, proba8, proba9, proba10)
        assert False
    except Exception as ex:
        assert (str(ex) == "participant existent!\n")
    id_participant_invalid = 'a'
    proba1_invalida = -1
    proba2_invalida = 20
    proba3_invalida = 30
    proba4_invalida = 40
    proba5_invalida = 50
    proba6_invalida = 60
    proba7_invalida = 70
    proba8_invalida = 80
    proba9_invalida = 90
    proba10_invalida = 100
    try:
        service_adauga_participant_in_lista(lista_participanti, id_participant_invalid, proba1_invalida,
                                            proba2_invalida, proba3_invalida, proba4_invalida, proba5_invalida,
                                            proba6_invalida, proba7_invalida, proba8_invalida, proba9_invalida,
                                            proba10_invalida)
        assert False
    except Exception as ex:
        assert "id invalid!" in str(ex)
        assert "proba 1 invalida" in str(ex)
        assert "proba 2 invalida" in str(ex)
        assert "proba 3 invalida" in str(ex)
        assert "proba 4 invalida" in str(ex)
        assert "proba 5 invalida" in str(ex)
        assert "proba 6 invalida" in str(ex)
        assert "proba 7 invalida" in str(ex)
        assert "proba 8 invalida" in str(ex)
        assert "proba 9 invalida" in str(ex)
        assert "proba 10 invalida" in str(ex)

def test_creeaza_participanti():
    id_participant = 1
    proba1 = 1
    proba2 = 2
    proba3 = 3
    proba4 = 4
    proba5 = 5
    proba6 = 6
    proba7 = 7
    proba8 = 8
    proba9 = 9
    proba10 = 10
    epsilon = 0.00001
    participant = creeaza_participant(id_participant, proba1, proba2, proba3, proba4, proba5, proba6, proba7, proba8,
                                                                                                 proba9, proba10)
    assert (id_participant-get_id_participant(participant) < epsilon)
    assert (proba1 - get_proba1(participant)) < epsilon
    assert (proba2 - get_proba2(participant)) < epsilon
    assert (proba3 - get_proba3(participant)) < epsilon
    assert (proba4 - get_proba4(participant)) < epsilon
    assert (proba5 - get_proba5(participant)) < epsilon
    assert (proba6 - get_proba6(participant)) < epsilon
    assert (proba7 - get_proba7(participant)) < epsilon
    assert (proba8 - get_proba8(participant)) < epsilon
    assert (proba9 - get_proba9(participant)) < epsilon
    assert (proba10 - get_proba10(participant)) < epsilon
def ruleaza_teste():
    test_creeaza_participanti()
    test_valideaza_participant()
    test_adauga_participant_in_lista_de_participanti()
    test_service_adauga_participant_in_lista_participanti()

def main_teste():
    ruleaza_teste()
    #run()
main_teste()
