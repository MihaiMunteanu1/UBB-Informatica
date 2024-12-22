from repo.repo_piese import FileRepoPiese
from domain.piesa import Piesa
from valid.validator_piesa import ValidatorPiesa
from service.service_piese import ServicePiese
class Teste:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier

    def __goleste_fisier(self):
        with open(self.__cale_fisier, 'w') as f:
            f.write('')
    def __test_adauga_piese_din_fisier_in_repo(self):
        repo=FileRepoPiese(self.__cale_fisier)
        piese=repo.get_all()
        assert len(piese)==10
    def __test_adauga_piesa(self):
        repo = FileRepoPiese(self.__cale_fisier)
        id=int(101)
        titlu='X'
        regizor='V'
        gen='Comedie'
        durata=int(100)
        piesa=Piesa(id,titlu,regizor,gen,durata)
        repo.add_piesa(piesa)
        assert len(repo.get_all())==11

        id_gresit = -2
        titlu_gresit = ''
        regizor_gresit = ''
        gen_gresit = 'Horror'
        durata_gresita = -4
        piesa_gresit = Piesa(id_gresit, titlu_gresit, regizor_gresit, gen_gresit, durata_gresita)
        validator=ValidatorPiesa()
        try:
            validator.valideaza_piesa(piesa_gresit)
            assert False
        except Exception:
            assert True

    def __test_modifica_piesa(self):
        titlu='A'
        regizor='Z'
        gen_modificat='Altele'
        durata_modificata=int(321)
        repo = FileRepoPiese(self.__cale_fisier)
        validator = ValidatorPiesa()
        validator.valideaza_piesa2(titlu,regizor,gen_modificat,durata_modificata)
        repo.modifica(titlu,regizor,gen_modificat,durata_modificata)
        piese=repo.get_all()
        for piesa in piese:
            if piesa.get_titlu()==titlu and piesa.get_regizor()==regizor:
                assert piesa.get_gen()==gen_modificat
                assert piesa.get_durata()==durata_modificata

    def __test_generare_random(self):
        numere=int(10)
        repo = FileRepoPiese(self.__cale_fisier)
        validator = ValidatorPiesa()
        srv_piesa=ServicePiese(repo,validator)
        srv_piesa.random(numere)
        assert len(repo.get_all())==21
    def run_all_tests(self):
        self.__test_adauga_piese_din_fisier_in_repo()
        self.__test_adauga_piesa()
        self.__test_modifica_piesa()
        self.__test_generare_random()