# Divisão de trabalho e integração

## Branches

```bash
git checkout -b feature/gameplay
```

```bash
git checkout -b feature/graphics
```

A branch `main` deve permanecer compilável.

## Pessoa responsável pela lógica

Arquivos principais:

- `Game.cpp/.h`
- `Player.cpp/.h`
- `Enemy.cpp/.h`
- `Projectile.cpp/.h`
- `Weapon.cpp/.h`
- `Collision.cpp/.h`
- `WaveManager.cpp/.h`

Próximas tarefas:

1. adicionar separação entre inimigos;
2. adicionar XP e level up;
3. criar segunda arma;
4. balancear ondas e tipos de inimigos;
5. adicionar vitória/chefe se houver tempo.

## Pessoa responsável pelos gráficos

Arquivos principais:

- `Renderer.cpp/.h`
- `Camera.cpp/.h`
- `Texture.cpp/.h`
- `HUD.cpp/.h`
- `Audio.cpp/.h`
- pasta `assets/`

Próximas tarefas:

1. substituir formas básicas por visual próprio;
2. melhorar iluminação e materiais;
3. adicionar texturas externas, se necessário;
4. desenhar XP e segunda arma quando existirem;
5. melhorar HUD e telas;
6. implementar áudio por último.

## Arquivos compartilhados

- `main.cpp`
- `Entity.h`
- `Input.h`
- `CMakeLists.txt`

Não alterar esses arquivos sem avisar a outra pessoa.

## Integração

Façam merge a cada funcionalidade pequena. Antes do merge:

```bash
cmake -S . -B build
cmake --build build -j
```

O primeiro marco conjunto é manter funcionando:

- jogador andando;
- inimigos perseguindo;
- projéteis automáticos;
- colisões;
- câmera, chão, iluminação e HUD.
