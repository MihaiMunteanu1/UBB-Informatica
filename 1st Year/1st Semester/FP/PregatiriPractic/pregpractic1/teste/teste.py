from repository.repo_emisiuni import RepositoryEmisiuniFiles
class Teste:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
    def __add_emisiun_repo(self):
        repo_emisiune=RepositoryEmisiuniFiles(self.__cale_fisier)
        emisiuni=repo_emisiune.get_all()
        assert len(emisiuni)==10

    def run_al_tests(self):
        self.__add_emisiun_repo()