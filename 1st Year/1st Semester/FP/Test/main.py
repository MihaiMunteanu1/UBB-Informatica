from teste.teste import Teste
test_cale_fisier="C:\\Users\\PycharmProjects\\test\\teste\\test_materiale.txt"
test_cale_fisier1="C:\\Users\\PycharmProjects\\test\\teste\\test_functionalitate_1.txt"
test_cale_fisier2="C:\\Users\\PycharmProjects\\test\\teste\\test_functionalitate_2.txt"
with open(test_cale_fisier2, "w") as f:
    f.write('')
with open(test_cale_fisier1, "w") as f:
    f.write('')
teste=Teste(test_cale_fisier,test_cale_fisier1,test_cale_fisier2)
teste.run_all_tests()

from repository.repo_materiale import RepositoryMaterialeFisiere
cale_fisier="C:\\Users\\PycharmProjects\\test\\materiale.txt"
cale_fisier1="C:\\Users\\PycharmProjects\\test\\functionalitate_1.txt"
cale_fisier2="C:\\Users\\PycharmProjects\\test\\functionalitate_2.txt"
with open(cale_fisier2, "w") as f:
    f.write('')
with open(cale_fisier1, "w") as f:
    f.write('')
repo_fisier=RepositoryMaterialeFisiere(cale_fisier,cale_fisier1,cale_fisier2)
from service.service_materiale import ServiceMateriale
srv_material=ServiceMateriale(repo_fisier)

from repository.repo_vanzare import RepositoryVanzarea
repo_vanzare=RepositoryVanzarea()
from service.service_vanzare import ServiceVanzare
srv_vanzare=ServiceVanzare(repo_vanzare)

from console.ui import UI
ui=UI(srv_material,srv_vanzare)
ui.run()
