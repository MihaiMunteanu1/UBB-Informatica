from teste.teste import Teste
cale_fisiser_teste='teste.txt'
teste=Teste(cale_fisiser_teste)
#teste.run_all_tests()

from repository.repository_tractoare import FileRepositoryTractoare
cale_fisier='tractoare.txt'
repository_tractoare=FileRepositoryTractoare(cale_fisier)

from validator.validator_tractor import ValidatorTractor
validator_tractor=ValidatorTractor()

from service.service_tractoare import ServiceTractoare
service_tractoare=ServiceTractoare(repository_tractoare,validator_tractor)
repository_tractoare.get_all()
from console.ui import UI
ui=UI(service_tractoare)
ui.run()
