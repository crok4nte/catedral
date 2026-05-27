# Catedral Teamserver

Source code of Catedral teamserver. Written in Golang.


### Build the Teamserver
- **Pre-requisites**
	1. Go 1.24+
- **Native**
	- To build the Teamserver locally, run the following command in the project root(`~/Catedral/`):
		1. `make ts-build`
	- That's it! If it ran successfully to completion, you should now have a compiled binary `catedral` ready for use.
	- Example use with a prewritten profile: `sudo ./catedral server --profile profiles/havoc.yaotl --verbose`
	- Example use with default profile: `sudo ./catedral --default --verbose`
- **Docker**
	- To build the Teamserver using a local Docker container, run the following commands(assuming you have Docker installed):
		1. Build the Dockerfile:
			* `sudo docker build -t catedral-teamserver -f Catedral-Dockerfile .`
		2. (Optional) Create a persistent data volume for the container:
			* `sudo docker volume create catedral-c2-data`
		3. Run the container:
			* `sudo docker run -it -d -v catedral-c2-data:/data catedral-teamserver`


### Run the Teamserver
- **Base:**
	- The teamserver can also be used directly:
		* `./catedral -h`
		* `./catedral server --profile profiles/havoc.yaotl -v`
		* `./catedral server --default -v`
- **Docker**
	- We can run the teamserver completely from within a container!
	1. Build the container: 
		* `sudo docker build -f Catedral-Dockerfile .`
	2. Launch the container (be sure to change the port mapping to match your environment):
		* `sudo docker run -p40056:40056 -p 443:443 -it -d -v catedral-c2-data:/data catedral-teamserver`
	3. Access the teamserver at `localhost:40056` using your Catedral client.
