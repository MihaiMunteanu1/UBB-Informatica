
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
def creeaza_participant(id_participant, proba1, proba2, proba3, proba4, proba5, proba6, proba7, proba8, proba9,proba10):
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
def test_add_participant():
    optiune = "ADD 1 2 3 4 5 6 7 8 9 10"
    id_p=int(0)
    optiune2 = optiune.split(" ")
    optiune2.pop(0)
    for i in range(10):
        optiune2[i]=int(optiune2[i])
    participant = creeaza_participant(id_p,optiune2[0],optiune2[1],optiune2[2],optiune2[3],optiune2[4],optiune2[5],
                                      optiune2[6],optiune2[7],optiune2[8],optiune2[9])
    epsilon=0.00001
    assert (id_p - get_id_participant(participant) < epsilon)
    assert (optiune2[0] - get_proba1(participant)) < epsilon
    assert (optiune2[1] - get_proba2(participant)) < epsilon
    assert (optiune2[2] - get_proba3(participant)) < epsilon
    assert (optiune2[3] - get_proba4(participant)) < epsilon
    assert (optiune2[4] - get_proba5(participant)) < epsilon
    assert (optiune2[5] - get_proba6(participant)) < epsilon
    assert (optiune2[6] - get_proba7(participant)) < epsilon
    assert (optiune2[7] - get_proba8(participant)) < epsilon
    assert (optiune2[8] - get_proba9(participant)) < epsilon
    assert (optiune2[9] - get_proba10(participant)) < epsilon


test_add_participant()