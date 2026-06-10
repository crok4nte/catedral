# Catedral — Rediseño UI (Fase 1)

Fecha: 2026-06-09

## Objetivo
Modernizar la UI del cliente Qt6 de Catedral: reemplazar el acento rojo por azul
acero sobre la base negra/gris, hacer el sidebar izquierdo desplegable (toggle
con animación) con iconos más pequeños, y pulir fluidez general. La auditoría de
bugs del C2 queda como Fase 2.

## Stack
- Cliente: Qt6 / C++20 (`client/`)
- Tema central: `client/data/themes/Catedral.qss` (395 líneas)
- Sidebar: `client/src/UserInterface/Widgets/CatedralSidebar.cc` + `.hpp`,
  instanciado en `client/src/Catedral/Catedral.cc::Start()`
- Iconos: `client/data/icons/sidebar/*.svg` (existen, fill blanco hardcoded)

## A. Recoloreado de tema (rojo → azul acero)
Todo en `Catedral.qss`. Paleta:
- Acento brillante `#E5484D` → `#5B7A99` (tabs activas, botones, foco, scrollbar
  handle, `border-left` del sidebar item activo). 16 ocurrencias.
- Selección/highlight oscuro `#4A1518` → `#1E2A38`.
- Hover de acento → `#6E8FB0`.
- Base negra y grises se mantienen: `#0E0E10`, `#161618`, `#1C1C1F`, `#2A2A2E`.
- **No tocar** los rojos de error de consola en `client/src/Util/ColorText.cpp`
  (son semánticos de error, no branding).

## B. Sidebar desplegable + iconos
`CatedralSidebar` pasa de QFrame fijo (60px, iconos 32px, botones 48px) a
desplegable:
- Botón **toggle** arriba (logo Catedral) alterna colapsado ↔ expandido.
- Colapsado: ancho ~48px, solo iconos (`ToolButtonIconOnly`).
- Expandido: ancho ~190px, icono + texto (`ToolButtonTextBesideIcon`).
- **Animación** de `maximumWidth`/`minimumWidth` con `QPropertyAnimation`
  (~200ms, `QEasingCurve::InOutCubic`).
- Estado **persistente** vía `QSettings`.
- Iconos más pequeños: `iconSize` 20px, botón colapsado 40px.
- Recoloreado de icono por estado (gris neutro reposo / azul acento activo) con
  tint `QPainter` (`CompositionMode_SourceIn`); el `border-left` azul sigue como
  indicador de item activo.

## C. Fluidez / pulido
- Animación del sidebar (arriba).
- Transiciones hover/pressed coherentes; radios y spacing consistentes en QSS.
- Responsividad: revisar timers/refrescos de tablas; arreglar lo trivial de bajo
  riesgo, derivar lo serio a Fase 2.

## D. Verificación
- `make client-build` (cmake + Qt6) debe compilar sin errores.
- Inspección visual de: sidebar colapsa/expande con animación, iconos pequeños,
  acento azul en lugar de rojo, sin rojo de branding residual.

## Fuera de alcance (Fase 2)
- Auditoría de bugs teamserver (Go) + cliente → `pocs.md` con severidad/impacto/PoC.
