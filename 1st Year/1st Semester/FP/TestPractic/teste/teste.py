from repository.repository_tractoare import FileRepositoryTractoare
from domain.tractor import Tractor
from validator.validator_tractor import ValidatorTractor
class Teste:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
    def __goleste_fisier(self):
        with open(self.__cale_fisier,'w') as f:
            f.write('')
    def __test_adauga_din_file_in_repo(self):
        """
        Functie care testeaza daca tractoarele din fisier au fost adaugate in repository
        :return:
        """
        self.__goleste_fisier()
        with open(self.__cale_fisier,'w') as f:
            f.write('1,trac1,1000,bmw,10:10:2024\n2,trac2,2000,audi,11:11:2022\n')
        repository_tractor_teste=FileRepositoryTractoare(self.__cale_fisier)
        assert len(repository_tractor_teste.get_all())==2

    def __test_adauga_tractor(self):
        """
        Functie care testeaza daca un tractor a fost adaugat in repository
        :return:
        """
        self.__goleste_fisier()
        id=int(1)
        denumire='tractor1'
        pret=int(1000)
        model='bmw'
        data='20:10:2025'
        tractor=Tractor(id,denumire,pret,model,data)
        validator_tractor=ValidatorTractor()
        validator_tractor.valideaza_tractor(tractor)
        repository_tractor_teste = FileRepositoryTractoare(self.__cale_fisier)
        assert len(repository_tractor_teste.get_all())==0
        repository_tractor_teste.add_tractor(tractor)
        assert len(repository_tractor_teste.get_all())==1

    def __test_valideaza_tractor(self):
        """
        Functie de test care valideaza un tractor
        :return:
        """
        validator_tractor = ValidatorTractor()
        id_gresit=int(-1)
        denumire_gresita = ''
        pret_gresit = int(-1000)
        model_gresit = ''
        data_gresita = ''
        tractor_gresit=Tractor(id_gresit,denumire_gresita,pret_gresit,model_gresit,data_gresita)
        try:
            validator_tractor.valideaza_tractor(tractor_gresit)
            assert False
        except Exception:
            assert True

        id = int(1)
        denumire = 'tractor1'
        pret = int(1000)
        model = 'bmw'
        data = '20:10:2025'
        tractor = Tractor(id, denumire, pret, model, data)
        validator_tractor.valideaza_tractor(tractor)
        try:
            validator_tractor.valideaza_tractor(tractor)
            assert True
        except Exception:
            assert False

    def __test_sterge_tractor(self):
        """
        Functie de test care verifica daca stergerea de tractoare functioneaza
        :return:
        """
        self.__goleste_fisier()
        with open(self.__cale_fisier,'w') as f:
            f.write('1,trac1,1000,bmw,10:10:2024\n2,trac2,2000,audi,11:11:2022')
        repository_tractor_test=FileRepositoryTractoare(self.__cale_fisier)
        repository_tractor_test.get_all()
        repository_tractor_test.sterge_tractor(1)
        assert len(repository_tractor_test.get_all())==1
        repository_tractor_test.sterge_tractor(4)
        assert len(repository_tractor_test.get_all()) == 1

    def __test_undo(self):
        """
        Functie de test care verifica daca functia undo functioneaza
        :return:
        """
        self.__goleste_fisier()
        with open(self.__cale_fisier, 'w') as f:
            f.write('1,trac1,1000,bmw,10:10:2024\n2,trac2,2000,audi,11:11:2022')
        repository_tractor_teste = FileRepositoryTractoare(self.__cale_fisier)
        repository_tractor_teste.get_all()
        repository_tractor_teste.sterge_tractor(1)
        assert len(repository_tractor_teste.get_all())==1
        repository_tractor_teste.undo()
        assert len(repository_tractor_teste.get_all())==2
        tractor=Tractor(3,'tractor3',1500,'seat','12:12:2023')
        repository_tractor_teste.add_tractor(tractor)
        assert len(repository_tractor_teste.get_all())==3
        repository_tractor_teste.undo()
        assert len(repository_tractor_teste.get_all())==2

    def __test_filtrare_tractoare(self):
        """
        Functie de test care verifica daca filtrarea tractoarelor are loc corect
        :return:
        """
        self.__goleste_fisier()
        with open(self.__cale_fisier, 'w') as f:
            f.write('1,trac1,1000,bmw,10:10:2024\n2,trac2,2000,audi,11:11:2022\n3,troc3,1500,seat,12;10:2022')
        repository_tractor_teste = FileRepositoryTractoare(self.__cale_fisier)
        repository_tractor_teste.get_all()
        assert len(repository_tractor_teste.get_all())==3

        text='tr'
        numar=1500
        result=repository_tractor_teste.filtreaza_tractoare(text,numar)
        assert result==['1,trac1,1000,bmw,10:10:2024']
        result2=repository_tractor_teste.filtreaza_tractoare('',1600)
        assert result2 == ['1,trac1,1000,bmw,10:10:2024','3,*troc3,1500,seat,12;10:2022']
        result3=repository_tractor_teste.filtreaza_tractoare('',-1)
        assert result3==[]
        result4=repository_tractor_teste.filtreaza_tractoare('t',-1)
        assert result4==['1,trac1,1000,bmw,10:10:2024','2,*trac2,2000,audi,11:11:2022','3,*troc3,1500,seat,12;10:2022']

    def run_all_tests(self):
        """
        Functie care apeleaza toata functiile de test
        :return:
        """
        self.__test_adauga_din_file_in_repo()
        self.__test_adauga_tractor()
        self.__test_valideaza_tractor()
        self.__test_sterge_tractor()
        self.__test_undo()
        self.__test_filtrare_tractoare()