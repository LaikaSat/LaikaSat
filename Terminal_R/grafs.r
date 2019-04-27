# Terminal grafica en R
# ~~ LaikaSAT ~~

# uso:
#     [terminal]$ Rscript grafs.r
#
# necesita la libreria "serial" para leer el puerto. para instalar,
# hacer install.packages desde una sesion interactiva de R:
#     [terminal]$ R
#     > install.packages("serial")

# ========================== CONFIGURACION ==========================
puerto <- "ttyACM0"
# archivo donde guardar los datos filtrados
archivo <- "datos"
cantidad_datos <- 7
# cada X iteraciones del bucle principal se actualizaran los graficos.
# con periodo_plot se configura este X
periodo_plot <- 500
# tamaño de la muestra de datos que mostrar en los graficos
ultimos <- 50
# colores de linea
col_temp <- "red"
col_hum <- "blue4"
col_alt <- "chartreuse4"
col_pr <- "chocolate3"
# ========================= /CONFIGURACION ==========================



library(serial)

# separa string en mas strings por espacios. por ejemplo:
# sep("DATA A B C D E F G FDATA")
# devuelve
# "DATA" "A" "B" "C" "D" "E" "F" "G" "FDATA"
sep <- function(str) {
    return(strsplit(str, " ", fixed=TRUE))
}

# sacar vector de numeros desde strings, devuelve NULL si algun valor
# es invalido. [cantidad preestablecida de elementos a leer?]
extractNums <- function(strs) {
    lst <- double()
    i <- 2  # los indexes en R empiezan por 1
    # al separar por espacios el primer espacio pasa a ser ""
    ln <- length(strs)
    if (ln == cantidad_datos + 1) {
        while (i <= ln) {
            # comprobamos si es un numero valido
            if (grepl("^-?[0-9]+($||.[0-9]+$)", strs[[i]])) {
                lst[[i-1]] <- as.numeric(strs[[i]])
                i <- i + 1
            } else
                return(NULL)
        }
        return(lst)
    } else
        return(NULL)
}

# vamos abriendo el puerto
con <- serialConnection(name=puerto, port=puerto, mode="9600,n,8,1", newline=1, translation="crlf")
open(con)

# index del paquete actual
datos_index <- 1

temp <- integer()
hum <- integer()
alt <- integer()
pr <- integer()

# añade un paquete de datos a cada vector que sera visualizado.
# se usa <<- en vez de <- para asignar valores a variables de scope
# exterior
addData <- function(data) { 
    if (!is.null(data)) {
        temp[[datos_index]] <<- data[[1]]
        hum[[datos_index]] <<- data[[2]]
        alt[[datos_index]] <<- data[[4]]
        pr[[datos_index]] <<- data[[3]]
        datos_index <<- datos_index + 1
    }
}

x11started <- FALSE
xl <- ""
periodo_plot_orig <- periodo_plot

write("======== DATOS LAIKASAT ========\n", archivo, append=TRUE)

while(TRUE) {
    txt <- as.character(read.serialConnection(con))
    # separamos el texto en paquetes, que a su vez separaremos en campos
    paquetes <- sapply(unlist(strsplit(txt, "FDATADATA|FDATA|DATA")), sep)
    # extraimos y guardamos los valores numericos
    nums <- sapply(paquetes, extractNums)
    sapply(nums, addData)
    if (length(nums) != 0)
        write(unlist(nums), file=archivo, ncolumns=cantidad_datos, append=TRUE)
    if (!x11started) {
        X11()
        x11started <- TRUE
    }
    periodo_plot <- periodo_plot - 1
    if (periodo_plot <= 0) {
        par(mfrow=c(2,2), lwd=2, xaxt="n", mar=c(2,4,4,2))
        plot(tail(temp,ultimos), col=col_temp, type="l", ylab="Temperatura (K)", xlab=xl)
        mtext("LaikaSAT", side = 3, line = -2, outer = TRUE,
              cex=1.5, col="#6d0f0f", family="mono", font=2)
        plot(tail(hum,ultimos), col=col_hum, type="l", ylab="Humedad (%)", xlab=xl)
        plot(tail(alt,ultimos), col=col_alt, type="l", ylab="Altitud (m)", xlab=xl)
        plot(tail(pr,ultimos), col=col_pr, type="l", ylab="Presión (Pa)", xlab=xl)
        periodo_plot <- periodo_plot_orig
    }
}

