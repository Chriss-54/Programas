def calcular_rol_pagos(nombre, sueldo_base):
    # Cálculo de ingresos
    horas_extra = float(input(f"Ingrese las horas extra trabajadas por {nombre}: "))
    valor_hora_extra = sueldo_base / 160 * 1.5  # Suponiendo 160 horas mensuales y 50% adicional
    ingreso_horas_extra = horas_extra * valor_hora_extra
    
    # Total ingresos
    total_ingresos = sueldo_base + ingreso_horas_extra
    
    # Cálculo de egresos
    aporte_iess = total_ingresos * 0.0945  # 9.45% de aporte personal al IESS
    prestamo = float(input(f"Ingrese el valor de préstamos a descontar para {nombre}: "))
    
    # Total egresos
    total_egresos = aporte_iess + prestamo
    
    # Valor neto a recibir
    valor_neto = total_ingresos - total_egresos
    
    # Mostrar resultados
    print(f"\nRol de Pagos para {nombre}")
    print("=" * 30)
    print("INGRESOS:")
    print(f"Sueldo base: ${sueldo_base:.2f}")
    print(f"Horas extra: ${ingreso_horas_extra:.2f}")
    print(f"Total ingresos: ${total_ingresos:.2f}")
    print("\nEGRESOS:")
    print(f"Aporte IESS: ${aporte_iess:.2f}")
    print(f"Préstamos: ${prestamo:.2f}")
    print(f"Total egresos: ${total_egresos:.2f}")
    print("=" * 30)
    print(f"VALOR NETO A RECIBIR: ${valor_neto:.2f}")

# Ejecución del programa
nombre_empleado = input("Ingrese el nombre del empleado: ")
sueldo_base = float(input(f"Ingrese el sueldo base de {nombre_empleado}: "))
calcular_rol_pagos(nombre_empleado, sueldo_base)