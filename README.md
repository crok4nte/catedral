# Catedral Framework

## Descripción

Catedral es un framework C2 post-explotación construido sobre la base de Havoc.
Mantiene compatibilidad total con el agente Demon mientras provee una experiencia
de operador con stack modernizado (Go 1.25, Qt6) y branding propio.


---

## Requisitos

| Componente | Requisito               |
|------------|-------------------------|
| Go         | 1.25+                   |
| C++        | C++20, GCC 11+          |
| Qt         | Qt6 (Core/Gui/Widgets/Network/WebSockets/Sql) |
| cmake      | 3.15+                   |
| Python     | 3.10 (Script API)       |

---

## Build

```bash
# Build completo (teamserver + cliente)
make all

# O por separado:
make ts-build     # produce: ./catedral
make client-build # produce: ./client/Catedral

# Si necesitas bind en puertos < 1024 (requiere sudo):
make setcap-server
```

### Build manual — teamserver

```bash
export PATH=~/go-1.25/bin:$PATH
cd teamserver
go build -ldflags="-s -w" -o ../catedral main.go
```

### Build manual — cliente

```bash
cd client
mkdir -p Build && cd Build
cmake ..
cmake --build . -- -j4
# Binario en: ../Catedral
```

---

## Uso

```bash
# Teamserver
./catedral server --profile profiles/catedral.yaotl

# Cliente (requiere display gráfico)
./client/Catedral





