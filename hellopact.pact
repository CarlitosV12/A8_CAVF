
(namespace "free")

;;Implementación de keysets
(define-keyset "free.admin-keyset" (read-keyset "admin-keyset"))

;; Definición del módulo asociado al keyset
(module hello-world-contract "free.admin-keyset"
  "Contrato inteligente básico de Hello World"

  (defschema esquema-nombre
    nombre:string
  )

  (deftable tabla-nombres:{esquema-nombre})

  ;;unción que almacena la variable
  (defun guardar-nombre (id:string nuevo-nombre:string)
    (insert tabla-nombres id {
      "nombre": nuevo-nombre
    })
    (format "Se guardó el nombre: {}" [nuevo-nombre])
  )

  ;; Saludo
  (defun saludar (id:string)
    (with-read tabla-nombres id { "nombre" := nombre-guardado }
      (format "Hello world, {}!" [nombre-guardado])
    )
  )
)

;; TAbla
(create-table tabla-nombres)
