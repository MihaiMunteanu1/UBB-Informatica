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
    from modificare_scor import sterge_scor
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
    from modificare_scor import sterge_interval_scor_participanti
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
    from modificare_scor import inlocuieste_scor
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

    from tiparire_lista_de_participanti import concurenti_cu_nota_mica
    assert concurenti_cu_nota_mica(participant, 2, 5) == [0, 2, 3, 4, 5, 6]

    epsilon = 0.00000000001
    from opertatii_pe_un_subset_de_participanti import media_scoruri_interval_dat
    assert (abs(media_scoruri_interval_dat(participant, 1, 3) - 4.77) < epsilon)

    from opertatii_pe_un_subset_de_participanti import scorul_minim_pentru_interval
    assert scorul_minim_pentru_interval(participant, 1, 3) == 1

    from opertatii_pe_un_subset_de_participanti import scor_multiplu_zece_interval_dat
    assert scor_multiplu_zece_interval_dat(participant, 1, 3) == []


def teste_filtrare():
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
    from filtrare import filtrare_participanti_scor_multiplu_nr
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

    from filtrare import filtrare_participanti_scor_mic_decat_scor_dat
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
    ]


def teste_toate():
    teste()
    teste_filtrare()
    teste_inlocuire_scor()
    test_sterge_sor()
    teste_sterge_interval_scor()