from service.service_examen import ServiceExamen
from validators.validator_examen import ValidatorExamen
from repository.repo_examen import RepositoryExamenFisier
cale_fisier="C:\\Users\\munte\\PycharmProjects\\preg_practic\\examene.txt"
repo_examen_fisier=RepositoryExamenFisier(cale_fisier)
valid_examen=ValidatorExamen()
srv_examen=ServiceExamen(repo_examen_fisier,valid_examen)

from console.ui import UI
ui=UI(srv_examen)
ui.run()
