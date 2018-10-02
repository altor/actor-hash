# Lancement de l'image docker

	docker build -t actor_hash .
	docker run --name actor_hash --rm=true -it actor_hash /bin/bash

# Utilisation

- lancement du serveur : `src/server &`
- arrêt du serveur : `src/cli 0`
- envoi des coordonnées géographiques à encoder : `src/cli 1 long lat`
	
# Test
	
- bibliothèque geohash : `tests/geohash_test`
- bibliothèque utils : `tests/utils_test`	

