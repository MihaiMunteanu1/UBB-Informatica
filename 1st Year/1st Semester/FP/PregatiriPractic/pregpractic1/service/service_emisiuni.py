import random
class ServiceEmisiuni:
    def __init__(self,repo,valid):
        self.__repo=repo
        self.__valid=valid
    def sterge(self,nume,tip):
        self.__repo.sterge(nume,tip)
    def update(self,nume,tip,durata,descriere):
        self.__repo.update(nume,tip,durata,descriere)
    def ore(self,ora_inceput,ora_sfarsir):
        return self.__repo.ore(ora_inceput,ora_sfarsir)

    def get_all(self):
        return self.__repo.get_all()